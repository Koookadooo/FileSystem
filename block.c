#include "block.h"
#include "image.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BLOCK_SIZE 4096

unsigned char *bread(int block_num, unsigned char *block) {
    // Seek to the block number and read the block
    if (lseek(image_fd, block_num * BLOCK_SIZE, SEEK_SET) == -1) {
        perror("Error seeking to block");
        return NULL;
    }
    if (read(image_fd, block, BLOCK_SIZE) != BLOCK_SIZE) {
        perror("Error reading block");
        return NULL;
    }
    return block;
}

void bwrite(int block_num, unsigned char *block) {
    // Seek to the block number and write the block
    if (lseek(image_fd, block_num * BLOCK_SIZE, SEEK_SET) == -1) {
        perror("Error seeking to block");
        return;
    }
    if (write(image_fd, block, BLOCK_SIZE) != BLOCK_SIZE) {
        perror("Error writing to block");
        return;
    }
}

