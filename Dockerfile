# This Dockerfile builds a Docker image which contains an ubuntu OS accompanied with OpenCV.
# Notice that Docker ubuntu doesn't support GUI, which makes it difficult to run OpenCV on Docker.
# To solve the problem above, install socat and xquartz on host's MacOS.
# If you get in troubles with instruction 'RUN apt-get ...', try it few more times.
# A better way to settle this problem is using VNC.
# author: wantSomeChips @ XDU


FROM dorowu/ubuntu-desktop-lxde-vnc:focal-arm64

WORKDIR /

RUN	apt-get update &&\
	apt-get install -y ca-certificates 

RUN	echo 'deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal main restricted universe multiverse' > /etc/apt/sources.list &&\
	echo 'deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-updates main restricted universe multiverse' >> /etc/apt/sources.list &&\
	echo 'deb https://mirrors.tuna.tsinghua.edu.cn/ubuntu-ports/ focal-backports main restricted universe multiverse' >> /etc/apt/sources.list &&\
	echo 'deb http://ports.ubuntu.com/ubuntu-ports/ focal-security main restricted universe multiverse' >> /etc/apt/sources.list

RUN	apt-get update && apt-get install -y vim g++ build-essential \
	libcurl4 pkg-config cmake libopenblas-dev \
	libeigen3-dev libtbb-dev libavcodec-dev \ 
	libavformat-dev libgstreamer-plugins-base1.0-dev \
	libgstreamer1.0-dev libswscale-dev libgtk-3-dev \
	libpng-dev libjpeg-dev libcanberra-gtk-module libcanberra-gtk3-module \
	git && apt-get -y upgrade

RUN mkdir opencv
RUN mkdir opencv_contrib

ADD opencv-4.6.0 /opencv/
ADD opencv_contrib-4.6.0 /opencv_contrib/

RUN mkdir /opencv/build

WORKDIR /opencv/build

RUN	cmake -DOPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules  ..
RUN	make -j5
RUN	make install
	
WORKDIR /

RUN rm -rf opencv
RUN rm -rf opencv_contrib

#ENTRYPOINT /bin/bash

