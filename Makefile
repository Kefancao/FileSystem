CXX = g++
CXXFLAGS = -std=c++14 -g
OBJECTS =  Exception.o bitMap.o disk.o inode.o filesystem.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = fileSystem

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
