mak: mak.cpp
	mpic++ ${CXXFLAGS} -Idistributed/ distributed/message_internal.c distributed/zeus_local.c distributed/maklib.cpp mak.cpp -o mak;

mak-run: mak
	@INPUT_PATH=`mktemp`;	\
	cat > $${INPUT_PATH};	\
	time mpirun -np 4 distributed/runner $${INPUT_PATH} ./mak;

kol: kol.cpp
	mpic++ ${CXXFLAGS} -Idistributed/ distributed/message_internal.c distributed/zeus_local.c distributed/kollib.cpp kol.cpp -o kol;

kol-run: kol
	@INPUT_PATH=`mktemp`;	\
	cat > $${INPUT_PATH};	\
	time mpirun -np 4 distributed/runner $${INPUT_PATH} ./kol;
