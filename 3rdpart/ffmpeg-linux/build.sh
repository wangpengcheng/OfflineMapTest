#! bin/bash

#安装相关依赖

sudo apt-get update -qq 

sudo apt-get -y install \
  autoconf \
  automake \
  build-essential \
  cmake \
  git-core \
  libass-dev \
  libfreetype6-dev \
  libsdl2-dev \
  libtool \
  libva-dev \
  libvdpau-dev \
  libvorbis-dev \
  libxcb1-dev \
  libxcb-shm0-dev \
  libxcb-xfixes0-dev \
  pkg-config \
  texinfo \
  wget \
  zlib1g-dev


#安装ffmpeg相关依赖
sudo apt-get install nasm yasm libx264-dev libx265-dev libnuma-dev libvpx-dev libfdk-aac-dev libmp3lame-dev libopus-dev

# 将运行文件添加到用户中
sudo ./run_time ~/bin


cd ./lib
# 将链接库拷贝到系统库中

sudo cp *.so* /lib/x86_64-linux-gnu
