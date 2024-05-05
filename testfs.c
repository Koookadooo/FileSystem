#define CTEST_ENABLE
#include "image.h"
#include "block.h"
#include "ctest.h"
#include <stdlib.h>

int main() {
    // Initialize testing variables and configure testing environment
    CTEST_VERBOSE(1);
    CTEST_COLOR(1);

    // Open the image file first and test opening
    CTEST_ASSERT(image_open("test.img", 1) != -1, "Open image file with truncation");

    // Prepare data for writing and then write to the block
    unsigned char block_write[4096];
    for (size_t i = 0; i < sizeof(block_write); i++) {
        block_write[i] = (unsigned char)(i % 256);
    }
    bwrite(7, block_write);  // Write to block 7
    CTEST_ASSERT(bread(7, block_write) != NULL, "Write block and read back");

    // Read back the data from the block and verify
    unsigned char block_read[4096];
    CTEST_ASSERT(bread(7, block_read) != NULL, "Read block");

    // Verify the block read matches the block written
    int blocks_match = 1;
    for (size_t i = 0; i < sizeof(block_read); i++) {
        if (block_read[i] != block_write[i]) {
            blocks_match = 0;
            break;
        }
    }
    CTEST_ASSERT(blocks_match, "Verify written block matches read block");

    // Test closing the image file
    CTEST_ASSERT(image_close() == 0, "Close image file");

    // Output test results
    CTEST_RESULTS();

    // Exit with the test status
    CTEST_EXIT();
}
