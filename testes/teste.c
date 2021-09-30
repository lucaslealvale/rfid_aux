#include "stdint.h"
#include "stdio.h"

#define MASK_RST (1 << 0)
#define MASK_EN (1 << 1)
#define MASK_CLR_FIFO 1 << 2
#define BASE_REG_SET 0
#define BASE_REG_TARI 1
#define BASE_REG_FIFO 2
#define BASE_REG_STATUS 3
#define BASE_ID 7
#define PACKET_STD_SIZE 12
#define data_package_size 26
#define data_mask_size 6
#define eop 0b00000000000000000000000000000000

int tari_test         = 0b111110100;
int command_test      = 0b11111111111111111111111111111111;
int command_test_size = 32;


// int check_fifo_full(){
//     //return IORD_32DIRECT(NIOS_RFID_PERIPHERAL_0_BASE,BASE_REG_STATUS<<3) & 1;}
//     return 0;}
// void send_package(int package){
//     //IOWR_32DIRECT(NIOS_RFID_PERIPHERAL_0_BASE, BASE_REG_FIFO << 2, package);
//     printf("Resume:data_to_fifo = %04X\n", package);
//     printf("---------------------------------------------------------- \n");
//     }
// void send_end_of_package(){
//     //IOWR_32DIRECT(NIOS_RFID_PERIPHERAL_0_BASE, BASE_REG_FIFO << 2, eop);}
//     printf("Resume:data_to_fifo = %04X\n", eop);
//     printf("---------------------------------------------------------- \n");
// //commands = [ 0b00001110001,
// //             0b11111111111,
// //             0b00000000011,
// //             0b01010100101,
// //             0b11001100110]
// void select_package(int commands[]){
// 	int commands_bits = sizeof(commands);
// 	int lengh_commands = commands_bits/sizeof(commands[0]);

// 	for(int command = 0;command < lengh_commands;command++ ){
// 		if(sizeof(commands[command]) ){
// 		mount_package(commands[command], command_test_size);
// 	}
// } // TODO

// void mount_package(int command, int size)
// {
//     int remain_bits_to_send = size;
//     int remain_package = command;
//     int last_package_size = size % data_package_size;

//     while (remain_bits_to_send > 0)
//     {
//         if (remain_bits_to_send > data_package_size)
//         {
//             int data_to_fifo = remain_package & 0x1A;
//             remain_package = remain_package >> 0x1A;
//             int32_t to_fifo = data_to_fifo << 6 | 0x1A;

//             while(check_fifo_full()){}

//             send_package(to_fifo);

//             remain_bits_to_send = remain_bits_to_send - 0x1A;
//         }
//         else
//         {
//             int data_to_fifo = remain_package;
//             remain_package = remain_package >> last_package_size;
//             int32_t to_fifo = data_to_fifo << 6 | last_package_size;

//             while(check_fifo_full()){}

//             send_package(to_fifo);
//             remain_bits_to_send = remain_bits_to_send - last_package_size;
//         }
//     }
//     send_end_of_package();
// }

int main()
{
    //IOWR_32DIRECT(NIOS_RFID_PERIPHERAL_0_BASE, BASE_REG_TARI << 2, tari_test);
    //IOWR_32DIRECT(NIOS_RFID_PERIPHERAL_0_BASE, BASE_REG_SET << 2, MASK_EN);
    // ack_init(&command_ack, 1234);
    // ack_build(&command_ack);
    //mount_package(command_ack.result_data, command_ack.size);
    //mount_package(command_test, command_test_size);
    int commands[4];
    commands[0] = 0b11111111111111111111111111111111; //32
    commands[1] = 0b00000000; //8
    commands[2] = 0b1111111111111111; //16
    commands[3] = 0b11111111111111111111111111111111; //32
    int commands_bits = sizeof(commands);
	int lengh_commands = commands_bits/sizeof(commands[0]);
    int c0 = sizeof(commands[0]);
	int c1 = commands[1];
    int c2 = commands[2];
    int c3 = sizeof(commands[3])/sizeof(int);

    printf("commands_bits = %d\nlengh_commands = %d\n", commands_bits, lengh_commands);
    printf("c0 = %04X\nc1 = %04X\nc2 = %04X\nc3 = %04X\n", c0,c1,c2,c3);
    unsigned bits, var = (c2 < 0) ? -c2 : c2;
    for(bits = 0; var != 0; ++bits) var >>= 1;
    printf("bits: %d, var: %d", bits, var);
    // for(int command = 0;command < lengh_commands;command++ ){
	// 	if(sizeof(commands[command]) )
	// 	mount_package(commands[command], command_test_size);
	// }
    return 0;
}


// printf("Resume:data_to_fifo = %04X\nmask_package = %04X\nremain_package= %04X\nto_fifo = %04X\n", data_to_fifo, last_package_size, remain_package, to_fifo);
// printf("---------------------------------------------------------- \n");
