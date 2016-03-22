#include "zeus.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mpi.h"

typedef struct ZeusLocalState {
  int outgoing_messages_left;
  int nof_nodes;
} ZeusLocalState;

static ZeusLocalState* GetZeusLocalState() {
  static ZeusLocalState zeus_local_state;
  if (zeus_local_state.nof_nodes == 0) {
	zeus_local_state.outgoing_messages_left = 1000;
	zeus_local_state.nof_nodes = ZEUS(NumberOfNodes)();
  }
  return &zeus_local_state;
}

static void Finalize() {
  MPI_Finalize();
}

static void CheckMpiInit() {
  static int done = 0;
  if (!done) {
    MPI_Init(NULL, NULL);
    atexit(Finalize);
  }
  done = 1;
}

int ZEUS(NumberOfNodes)() {
  CheckMpiInit();
  int size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  return size;
}

ZEUS(NodeId) ZEUS(MyNodeId)() {
  CheckMpiInit();
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  return rank;
}

void ZEUS(Send)(ZEUS(NodeId) target, const char* message, int bytes) {
  CheckMpiInit();
  ZeusLocalState *zeus_local_state = GetZeusLocalState();
  if (target < 0 || target >= zeus_local_state->nof_nodes) {
    fprintf(stderr, "%d is not a valid target node, will exit now!!!", target);
    exit(1);
  }

  if (zeus_local_state->outgoing_messages_left == 0) {
    fprintf(stderr, "Limit for outgoing messages was reached!!!, will exit now");
    exit(1);
  }
  zeus_local_state->outgoing_messages_left--;

  char * buffer = (char*)malloc(bytes);
  assert(buffer);
  memcpy(buffer, message, bytes);
  MPI_Request mpi_request;
  MPI_Isend(buffer, bytes, MPI_CHAR, target, 0, MPI_COMM_WORLD, &mpi_request);
  MPI_Request_free(&mpi_request);
}

ZEUS(MessageInfo) ZEUS(Receive)(ZEUS(NodeId) source, char* buffer, int buffer_size) {
  CheckMpiInit();
  ZeusLocalState *zeus_local_state = GetZeusLocalState();
  if (source < -1 || source >= zeus_local_state->nof_nodes) {
    fprintf(stderr, "%d is not a valid receive source, will exit now!!!", source);
    exit(1);
  }

  MPI_Status status;
  int bytes_received = MPI_Recv(buffer, buffer_size, MPI_CHAR, source, 0, MPI_COMM_WORLD, &status);
  MPI_Get_count(&status, MPI_CHAR, &bytes_received);
  ZEUS(MessageInfo) mi;
  mi.sender_id = status.MPI_SOURCE;
  mi.length = bytes_received;
  return mi;
}

