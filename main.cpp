#include "AVL.cpp"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <cstring>
#include <linux/if_ether.h>

using namespace std;

int main(){
    int sock;
    int data;
    int count = 0;
    struct sockaddr saddr;

    //Allocates 200 bytes to buffer.
	unsigned char *buffer = (unsigned char *)malloc(200);

    //Initialize avl tree
    AVL myavl;

    //Open a socket
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP)); 
	
    if (sock < 0){
        cout << "Socket error\n";
        return 1;
    }

    cout << "Starting..." << endl;
    while (true && count <= 100) {
        count = 0;
        //Clear buffer to all 0s
        memset(buffer, 0, 200);
        //Receive data from socket and store in buffer
        data = recv(sock, buffer, 200, 0);

        if (data < 0){
            cout << "Recvfrom error";
            return 1;
        }

        //Create header to parse ip information
	    struct iphdr *ip = (struct iphdr *)(buffer + sizeof(struct ethhdr));
        
        //Declare, initialize, and insert AVL_node into AVL tree
        shared_ptr<avl_node> new_node (new avl_node);
        new_node = myavl.InitNode(ip->protocol, ip->saddr, ip->daddr);
        myavl.InsertNode(new_node);
        //Update count based on number of unique source IP addresses
        shared_ptr<avl_node> root = myavl.GetRoot();
        count = myavl.PacketsRecvd(root, count);
    }
    
    close(sock);
    cout << "Done!" << endl;
    shared_ptr<avl_node> root = myavl.GetRoot();

    //Test whether avl tree functions properly.
    cout << "Root: " << (unsigned int)root->source << endl;
    myavl.TestTraverseTreeInorder(root);

    return 0;
}