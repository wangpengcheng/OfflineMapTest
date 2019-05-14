#!/bin/bash

#直接安装
sudo add-apt-repository ppa:djcj/hybrid
sudo apt-get update
sudo apt-get -y install ffmpeg

# 安装相关解码依赖，264,265
sudo apt-get -y x264 x265
