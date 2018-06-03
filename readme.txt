group members: 
Gary Kattan
Muhammad Ammar Chohan

We have implemented the following functionalities:

ext2_cp.c:  The C file that implements ext_cp
ext2_mkdir.c:  The C file that implements ext_mkdir
ext2_ln.c:  The C file that implements ext_ln
ext2_rm.c:  The C file that implements ext_rm
ext2_touch.c: The C file that implements ext_touch
ext2_utils.c:  This file contains the utility functions that are shared by different programs.
Makefile: 	The Makefile that compiles all the programs


Instructions for making and mounting disk images: 
% dd if=/dev/zero of=~/DISKNAME.img bs=1024 count=128
% mke2fs -N 32 DISKNAME.img
% sudo mount -o loop ~/DISKNAME.img /.../mntpoint
% check to see if it is mounted: df -hl
% cd /.../mntpoint
% ...... normal linux commands to add/remove files/directories/links .....
% cd /.../mntpoint
% umount /..../mntpoint


Extra information
A disk is 128 blocks where the block size is 1024 bytes.
There is only one block group.
There are 32 inodes.
You do not have to worry about permissions or modified time fields in the inodes. You should set the
type (in i_mode), i_size, i_links_count, i_blocks(disk sectors), and the i_block array.
