# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kiseshi/NetWings

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kiseshi/NetWings

# Include any dependencies generated for this target.
include net/CMakeFiles/net.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include net/CMakeFiles/net.dir/compiler_depend.make

# Include the progress variables for this target.
include net/CMakeFiles/net.dir/progress.make

# Include the compile flags for this target's objects.
include net/CMakeFiles/net.dir/flags.make

net/CMakeFiles/net.dir/Acceptor.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Acceptor.cpp.o: net/Acceptor.cpp
net/CMakeFiles/net.dir/Acceptor.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object net/CMakeFiles/net.dir/Acceptor.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Acceptor.cpp.o -MF CMakeFiles/net.dir/Acceptor.cpp.o.d -o CMakeFiles/net.dir/Acceptor.cpp.o -c /home/kiseshi/NetWings/net/Acceptor.cpp

net/CMakeFiles/net.dir/Acceptor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Acceptor.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Acceptor.cpp > CMakeFiles/net.dir/Acceptor.cpp.i

net/CMakeFiles/net.dir/Acceptor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Acceptor.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Acceptor.cpp -o CMakeFiles/net.dir/Acceptor.cpp.s

net/CMakeFiles/net.dir/Buffer.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Buffer.cpp.o: net/Buffer.cpp
net/CMakeFiles/net.dir/Buffer.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object net/CMakeFiles/net.dir/Buffer.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Buffer.cpp.o -MF CMakeFiles/net.dir/Buffer.cpp.o.d -o CMakeFiles/net.dir/Buffer.cpp.o -c /home/kiseshi/NetWings/net/Buffer.cpp

net/CMakeFiles/net.dir/Buffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Buffer.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Buffer.cpp > CMakeFiles/net.dir/Buffer.cpp.i

net/CMakeFiles/net.dir/Buffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Buffer.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Buffer.cpp -o CMakeFiles/net.dir/Buffer.cpp.s

net/CMakeFiles/net.dir/Channel.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Channel.cpp.o: net/Channel.cpp
net/CMakeFiles/net.dir/Channel.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object net/CMakeFiles/net.dir/Channel.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Channel.cpp.o -MF CMakeFiles/net.dir/Channel.cpp.o.d -o CMakeFiles/net.dir/Channel.cpp.o -c /home/kiseshi/NetWings/net/Channel.cpp

net/CMakeFiles/net.dir/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Channel.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Channel.cpp > CMakeFiles/net.dir/Channel.cpp.i

net/CMakeFiles/net.dir/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Channel.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Channel.cpp -o CMakeFiles/net.dir/Channel.cpp.s

net/CMakeFiles/net.dir/CurrentThread.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/CurrentThread.cpp.o: net/CurrentThread.cpp
net/CMakeFiles/net.dir/CurrentThread.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object net/CMakeFiles/net.dir/CurrentThread.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/CurrentThread.cpp.o -MF CMakeFiles/net.dir/CurrentThread.cpp.o.d -o CMakeFiles/net.dir/CurrentThread.cpp.o -c /home/kiseshi/NetWings/net/CurrentThread.cpp

net/CMakeFiles/net.dir/CurrentThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/CurrentThread.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/CurrentThread.cpp > CMakeFiles/net.dir/CurrentThread.cpp.i

net/CMakeFiles/net.dir/CurrentThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/CurrentThread.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/CurrentThread.cpp -o CMakeFiles/net.dir/CurrentThread.cpp.s

net/CMakeFiles/net.dir/DefaultPoller.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/DefaultPoller.cpp.o: net/DefaultPoller.cpp
net/CMakeFiles/net.dir/DefaultPoller.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object net/CMakeFiles/net.dir/DefaultPoller.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/DefaultPoller.cpp.o -MF CMakeFiles/net.dir/DefaultPoller.cpp.o.d -o CMakeFiles/net.dir/DefaultPoller.cpp.o -c /home/kiseshi/NetWings/net/DefaultPoller.cpp

net/CMakeFiles/net.dir/DefaultPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/DefaultPoller.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/DefaultPoller.cpp > CMakeFiles/net.dir/DefaultPoller.cpp.i

net/CMakeFiles/net.dir/DefaultPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/DefaultPoller.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/DefaultPoller.cpp -o CMakeFiles/net.dir/DefaultPoller.cpp.s

net/CMakeFiles/net.dir/EpollPoller.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/EpollPoller.cpp.o: net/EpollPoller.cpp
net/CMakeFiles/net.dir/EpollPoller.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object net/CMakeFiles/net.dir/EpollPoller.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/EpollPoller.cpp.o -MF CMakeFiles/net.dir/EpollPoller.cpp.o.d -o CMakeFiles/net.dir/EpollPoller.cpp.o -c /home/kiseshi/NetWings/net/EpollPoller.cpp

net/CMakeFiles/net.dir/EpollPoller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/EpollPoller.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/EpollPoller.cpp > CMakeFiles/net.dir/EpollPoller.cpp.i

net/CMakeFiles/net.dir/EpollPoller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/EpollPoller.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/EpollPoller.cpp -o CMakeFiles/net.dir/EpollPoller.cpp.s

net/CMakeFiles/net.dir/EventLoop.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/EventLoop.cpp.o: net/EventLoop.cpp
net/CMakeFiles/net.dir/EventLoop.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object net/CMakeFiles/net.dir/EventLoop.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/EventLoop.cpp.o -MF CMakeFiles/net.dir/EventLoop.cpp.o.d -o CMakeFiles/net.dir/EventLoop.cpp.o -c /home/kiseshi/NetWings/net/EventLoop.cpp

net/CMakeFiles/net.dir/EventLoop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/EventLoop.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/EventLoop.cpp > CMakeFiles/net.dir/EventLoop.cpp.i

net/CMakeFiles/net.dir/EventLoop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/EventLoop.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/EventLoop.cpp -o CMakeFiles/net.dir/EventLoop.cpp.s

net/CMakeFiles/net.dir/EventLoopThread.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/EventLoopThread.cpp.o: net/EventLoopThread.cpp
net/CMakeFiles/net.dir/EventLoopThread.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object net/CMakeFiles/net.dir/EventLoopThread.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/EventLoopThread.cpp.o -MF CMakeFiles/net.dir/EventLoopThread.cpp.o.d -o CMakeFiles/net.dir/EventLoopThread.cpp.o -c /home/kiseshi/NetWings/net/EventLoopThread.cpp

net/CMakeFiles/net.dir/EventLoopThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/EventLoopThread.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/EventLoopThread.cpp > CMakeFiles/net.dir/EventLoopThread.cpp.i

net/CMakeFiles/net.dir/EventLoopThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/EventLoopThread.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/EventLoopThread.cpp -o CMakeFiles/net.dir/EventLoopThread.cpp.s

net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o: net/EventLoopThreadPool.cpp
net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o -MF CMakeFiles/net.dir/EventLoopThreadPool.cpp.o.d -o CMakeFiles/net.dir/EventLoopThreadPool.cpp.o -c /home/kiseshi/NetWings/net/EventLoopThreadPool.cpp

net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/EventLoopThreadPool.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/EventLoopThreadPool.cpp > CMakeFiles/net.dir/EventLoopThreadPool.cpp.i

net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/EventLoopThreadPool.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/EventLoopThreadPool.cpp -o CMakeFiles/net.dir/EventLoopThreadPool.cpp.s

net/CMakeFiles/net.dir/InetAddress.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/InetAddress.cpp.o: net/InetAddress.cpp
net/CMakeFiles/net.dir/InetAddress.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object net/CMakeFiles/net.dir/InetAddress.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/InetAddress.cpp.o -MF CMakeFiles/net.dir/InetAddress.cpp.o.d -o CMakeFiles/net.dir/InetAddress.cpp.o -c /home/kiseshi/NetWings/net/InetAddress.cpp

net/CMakeFiles/net.dir/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/InetAddress.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/InetAddress.cpp > CMakeFiles/net.dir/InetAddress.cpp.i

net/CMakeFiles/net.dir/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/InetAddress.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/InetAddress.cpp -o CMakeFiles/net.dir/InetAddress.cpp.s

net/CMakeFiles/net.dir/Poller.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Poller.cpp.o: net/Poller.cpp
net/CMakeFiles/net.dir/Poller.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object net/CMakeFiles/net.dir/Poller.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Poller.cpp.o -MF CMakeFiles/net.dir/Poller.cpp.o.d -o CMakeFiles/net.dir/Poller.cpp.o -c /home/kiseshi/NetWings/net/Poller.cpp

net/CMakeFiles/net.dir/Poller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Poller.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Poller.cpp > CMakeFiles/net.dir/Poller.cpp.i

net/CMakeFiles/net.dir/Poller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Poller.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Poller.cpp -o CMakeFiles/net.dir/Poller.cpp.s

net/CMakeFiles/net.dir/Socket.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Socket.cpp.o: net/Socket.cpp
net/CMakeFiles/net.dir/Socket.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object net/CMakeFiles/net.dir/Socket.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Socket.cpp.o -MF CMakeFiles/net.dir/Socket.cpp.o.d -o CMakeFiles/net.dir/Socket.cpp.o -c /home/kiseshi/NetWings/net/Socket.cpp

net/CMakeFiles/net.dir/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Socket.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Socket.cpp > CMakeFiles/net.dir/Socket.cpp.i

net/CMakeFiles/net.dir/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Socket.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Socket.cpp -o CMakeFiles/net.dir/Socket.cpp.s

net/CMakeFiles/net.dir/TcpConnection.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/TcpConnection.cpp.o: net/TcpConnection.cpp
net/CMakeFiles/net.dir/TcpConnection.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object net/CMakeFiles/net.dir/TcpConnection.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/TcpConnection.cpp.o -MF CMakeFiles/net.dir/TcpConnection.cpp.o.d -o CMakeFiles/net.dir/TcpConnection.cpp.o -c /home/kiseshi/NetWings/net/TcpConnection.cpp

net/CMakeFiles/net.dir/TcpConnection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/TcpConnection.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/TcpConnection.cpp > CMakeFiles/net.dir/TcpConnection.cpp.i

net/CMakeFiles/net.dir/TcpConnection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/TcpConnection.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/TcpConnection.cpp -o CMakeFiles/net.dir/TcpConnection.cpp.s

net/CMakeFiles/net.dir/TcpServer.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/TcpServer.cpp.o: net/TcpServer.cpp
net/CMakeFiles/net.dir/TcpServer.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object net/CMakeFiles/net.dir/TcpServer.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/TcpServer.cpp.o -MF CMakeFiles/net.dir/TcpServer.cpp.o.d -o CMakeFiles/net.dir/TcpServer.cpp.o -c /home/kiseshi/NetWings/net/TcpServer.cpp

net/CMakeFiles/net.dir/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/TcpServer.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/TcpServer.cpp > CMakeFiles/net.dir/TcpServer.cpp.i

net/CMakeFiles/net.dir/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/TcpServer.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/TcpServer.cpp -o CMakeFiles/net.dir/TcpServer.cpp.s

net/CMakeFiles/net.dir/Thread.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/Thread.cpp.o: net/Thread.cpp
net/CMakeFiles/net.dir/Thread.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object net/CMakeFiles/net.dir/Thread.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/Thread.cpp.o -MF CMakeFiles/net.dir/Thread.cpp.o.d -o CMakeFiles/net.dir/Thread.cpp.o -c /home/kiseshi/NetWings/net/Thread.cpp

net/CMakeFiles/net.dir/Thread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/Thread.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/Thread.cpp > CMakeFiles/net.dir/Thread.cpp.i

net/CMakeFiles/net.dir/Thread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/Thread.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/Thread.cpp -o CMakeFiles/net.dir/Thread.cpp.s

net/CMakeFiles/net.dir/TimeStamp.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/TimeStamp.cpp.o: net/TimeStamp.cpp
net/CMakeFiles/net.dir/TimeStamp.cpp.o: net/CMakeFiles/net.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kiseshi/NetWings/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object net/CMakeFiles/net.dir/TimeStamp.cpp.o"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT net/CMakeFiles/net.dir/TimeStamp.cpp.o -MF CMakeFiles/net.dir/TimeStamp.cpp.o.d -o CMakeFiles/net.dir/TimeStamp.cpp.o -c /home/kiseshi/NetWings/net/TimeStamp.cpp

net/CMakeFiles/net.dir/TimeStamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/TimeStamp.cpp.i"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kiseshi/NetWings/net/TimeStamp.cpp > CMakeFiles/net.dir/TimeStamp.cpp.i

net/CMakeFiles/net.dir/TimeStamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/TimeStamp.cpp.s"
	cd /home/kiseshi/NetWings/net && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kiseshi/NetWings/net/TimeStamp.cpp -o CMakeFiles/net.dir/TimeStamp.cpp.s

net: net/CMakeFiles/net.dir/Acceptor.cpp.o
net: net/CMakeFiles/net.dir/Buffer.cpp.o
net: net/CMakeFiles/net.dir/Channel.cpp.o
net: net/CMakeFiles/net.dir/CurrentThread.cpp.o
net: net/CMakeFiles/net.dir/DefaultPoller.cpp.o
net: net/CMakeFiles/net.dir/EpollPoller.cpp.o
net: net/CMakeFiles/net.dir/EventLoop.cpp.o
net: net/CMakeFiles/net.dir/EventLoopThread.cpp.o
net: net/CMakeFiles/net.dir/EventLoopThreadPool.cpp.o
net: net/CMakeFiles/net.dir/InetAddress.cpp.o
net: net/CMakeFiles/net.dir/Poller.cpp.o
net: net/CMakeFiles/net.dir/Socket.cpp.o
net: net/CMakeFiles/net.dir/TcpConnection.cpp.o
net: net/CMakeFiles/net.dir/TcpServer.cpp.o
net: net/CMakeFiles/net.dir/Thread.cpp.o
net: net/CMakeFiles/net.dir/TimeStamp.cpp.o
net: net/CMakeFiles/net.dir/build.make
.PHONY : net

# Rule to build all files generated by this target.
net/CMakeFiles/net.dir/build: net
.PHONY : net/CMakeFiles/net.dir/build

net/CMakeFiles/net.dir/clean:
	cd /home/kiseshi/NetWings/net && $(CMAKE_COMMAND) -P CMakeFiles/net.dir/cmake_clean.cmake
.PHONY : net/CMakeFiles/net.dir/clean

net/CMakeFiles/net.dir/depend:
	cd /home/kiseshi/NetWings && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kiseshi/NetWings /home/kiseshi/NetWings/net /home/kiseshi/NetWings /home/kiseshi/NetWings/net /home/kiseshi/NetWings/net/CMakeFiles/net.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : net/CMakeFiles/net.dir/depend
