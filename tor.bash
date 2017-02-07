#!/bin/bash
base_socks_port=9050
base_http_port=3129
base_control_port=8118
echo "Matant tors i proxy!"
killall tor
killall dg9_9_13

if [ ! -d "data" ]; then
        mkdir "data"
fi

for i in {0..9}
do
        j=$((i+1))
        socks_port=$((base_socks_port+i))
        control_port=$((base_control_port+i))
	http_port=$((base_http_port+i))
        if [ ! -d "data/tor$i" ]; then
                echo "Creant directori: data/tor$i"
                mkdir "data/tor$i"
        fi

        echo "Tor --> Control Port: $control_port Sockets: $socks_port"
        tor --RunAsDaemon 1 --CookieAuthentication 0 --HashedControlPassword "" --ControlPort $control_port --PidFile tor$i.pid --SocksPort $socks_port --DataDirectory data/tor$i > /dev/null
        echo    "HTTP PROXY --> HTTP PORT \"$http_port\" TO SOCKET $socks_port"
         /root/tor/delegate9.9.13/inst/dg9_9_13/DGROOT/bin/dg9_9_13 -P$http_port SERVER=http SOCKS=localhost:$socks_port CACHE=no LOGFILE="" -vs delegated HOSTLIST="*"
done
