#include <stdio.h>
#include <stdlib.h>

void net_public_ip() {
    printf("[Kynto NET] Fetching Public IP...\n");
    system("curl -s https://ifconfig.me && echo");
}

void net_local_ip() {
    printf("[Kynto NET] Local IP: ");
    // Usando barras duplas para o C não reclamar do escape sequence
    system("ip route get 1.1.1.1 | grep -oP 'src \\K\\S+'");
}

void net_dns() {
    printf("[Kynto NET] Google DNS Status: ");
    system("nslookup google.com | grep 'Address' | head -n 1");
}

void net_ports() {
    printf("[Kynto NET] Checking open local ports...\n");
    system("netstat -tuln | grep LISTEN | head -n 3");
}

void net_wifi() {
    printf("[Kynto NET] WiFi Interface: ");
    system("nmcli -t -f active,ssid dev wifi | grep '^yes' | cut -d: -f2 || echo 'Not connected'");
}
