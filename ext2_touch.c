#include "ext2_utils.h"

/*
ext2_touch: 

This program takes two command line arguments. 

The first is the name of an ext2 formatted virtual disk. 
The second is an absolute path on your ext2 formatted disk. 

The program should work like touch, creating a file on the specified path on the disk. If any component on 
the path to the location where the file is to be created does not exist or if the specified file already 
exists, then your program should return the appropriate error (ENOENT or EEXIST).
*/

//pointer to disk image in memory
extern unsigned char * disk;

// super block pointer sb
extern struct ext2_super_block *sb;

// block descriptor pointer bd
extern struct ext2_group_desc *bd;

//points to inode table
extern struct ext2_inode *pn; 

int main(int argc, char **argv) {
	if(argc != 3) {
        fprintf(stderr, "Usage: readimg <image file name> absolute path <ex. /dir1/dir2/newFile>\n");
        exit(1);
    }
	
	int component_inode;
	char * tokens_parent[MAX_TOKENS]; //tokens of parent path
	char * tokens_component[MAX_TOKENS];//tokens of absolute path
	char parentpath[MAXPATH_LENGTH];
	char component[MAX_FILE_NAME];
	
	//get path of parent directory and name of component
	extract_parentpath_component(argv[2], parentpath, component);
	
	struct comp_inode_type comp_i_t, parent_i_t;
	struct comp_inode_type *comp_it_p = &comp_i_t;
	struct comp_inode_type *parent_it_p = &parent_i_t;
	
	parsePath(argv[2], tokens_component);
	parsePath(parentpath, tokens_parent);
	
	comp_i_t.inode = 0;
	comp_i_t.file_type = 0;
	
	parent_i_t.inode = 0;
	parent_i_t.file_type = 0;
	
	loadImage(argv[1]); // loads disk image onto memory - load filesystem
	
	//is there another object in parent directory with the same name?
	comp_it_p = getObjectInode(tokens_component, comp_it_p);
	
	if(comp_it_p->inode != 0) {//there is
		// another component with the same name already exists in parent directory
		fprintf( stderr, strerror(EEXIST));
		fprintf( stderr, "\n");
		exit(1);
	}
	
	//get inode of parent directory
	parent_it_p = getObjectInode(tokens_parent, parent_it_p);
	
	//find a vacant inode for the directory we're about to created
	component_inode = find_vacantInode();
	bd->bg_free_inodes_count--;
	sb->s_free_inodes_count--;
	
	//create an entry for component in parent directory
	insertRecord(parent_it_p->inode, component_inode, component, EXT2_FT_REG_FILE);
	
    return 0;
}