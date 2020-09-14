#ffmpeg -re -i /dev/video0 -vcodec libx265 -acodec copy -rtsp_transport udp  -f rtsp rtsp://118.24.113.233:554/test



for((;;)); do \
        ffmpeg -re -i /dev/video0 \
        -vcodec libx265 -acodec copy \
        -tune zerolatency  -preset ultrafast \
        -rtsp_transport udp \
        -f rtsp -y rtsp://118.24.113.233:554/test; 
        sleep 1; \
    done
