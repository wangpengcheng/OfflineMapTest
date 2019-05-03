#ffmpeg -re -i /dev/video0 -vcodec libx265 -acodec copy -rtsp_transport udp  -f rtsp rtsp://localhost/test



for((;;)); do \
        ffmpeg -re -i /dev/video0 \
        -vcodec libx265 -acodec copy \
        -rtsp_transport udp \
        -f rtsp -y rtsp://192.168.137.165/test; 
        sleep 1; \
    done
