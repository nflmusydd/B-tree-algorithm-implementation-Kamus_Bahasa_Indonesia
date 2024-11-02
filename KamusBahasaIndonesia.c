#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>

/*
										        B-Tree
                                         Kamus Bahasa Indonesia

Username = user
Password = pass
*/

#define MIN_DEGREE 3

struct BTreeNode{
    int numKeys;
    char** keys;
    char** kbenda;
    char** kkerja;
    struct BTreeNode** children;
    int isLeaf;
};

bool adminlogin();
void lowerCase(char *);
void readFile(struct BTreeNode **);
struct BTreeNode* createNode();
bool keyExists(struct BTreeNode *, char *);
void insert(struct BTreeNode **, char *, char *, char *);
void splitChild(struct BTreeNode *, int );
void insertNonFull(struct BTreeNode *, char *, char *, char *);
int hapus(struct BTreeNode *, char *);
void borrowFromLeftSibling(struct BTreeNode *, int );
void borrowFromRightSibling(struct BTreeNode *, int );
void mergeChildren(struct BTreeNode *, int );
void updatekbenda(struct BTreeNode *, char *, char *);
void updatekkerja(struct BTreeNode *, char *, char *);
struct BTreeNode* search(struct BTreeNode *, char *);
void searchKey(struct BTreeNode *, char *);
void display(struct BTreeNode *);
void tabel(struct BTreeNode *);
void deleteAll(struct BTreeNode *);
void judulinsert();
void judulupdate();
void judulcari();
void judulhapus();
void judulhapusall();
void juduladmin();
void judulkamus();

int main(){
    struct BTreeNode* root = createNode();
    int cho, cho1, cho2, choup, chodel, c, c1, c2, cup, cdel;
    char key[26], kbenda[51], kkerja[51], nextch, nextch1, nextch2, nextchup, nextchdel;
    
    readFile(&root);
        
    do{
	    do{
			system("cls");
			printf("\033[1;94m"); 
    		printf("\t\t\t\t   ______________________________\n\n");
			printf("\t\t\t\t\t   Selamat Datang\n");
    		printf("\t\t\t\t   ______________________________\n\n\n");
    		printf("\033[0m"); 
		    printf("\t\t\t\t   \033[0;92m[1]\033[0m \033[0;91mMasuk Sebagai Admin\033[0m\n");
		    printf("\t\t\t\t   \033[0;92m[2]\033[0m \033[0;91mMasuk Sebagai Pengunjung\033[0m\n");
		    printf("\n\t\t\t\t   \033[0;92m[0]\033[0m \033[0;91mKeluar\033[0m\n");
		    
			printf("\n\t\t\t\t   \033[0;92m>> ");
			c = scanf("%d%c", &cho, &nextch);
            printf("\033[0m");
			fflush(stdin);
			if(c == 0 || nextch != '\n'){
				printf("\t\t\t\t   \033[0;92mPilih Angka yang tersedia!\033[0m\n");
				getch();
			}
		}while(c == 0 || nextch != '\n');
		
		if(cho == 1){
            system("cls");
            juduladmin();
            if(adminlogin() == false){
                getch();
                main();
                break;
            }

            do{
				do{
					system("cls");
                    juduladmin();
					printf("\t\t\t\t   \033[0;92m[1]\033[0m \033[0;91mSisipkan Data Baru\033[0m\n");
					printf("\t\t\t\t   \033[0;92m[2]\033[0m \033[0;91mPerbarui Data\033[0m\n");
					printf("\t\t\t\t   \033[0;92m[3]\033[0m \033[0;91mCari Data\033[0m\n");
					printf("\t\t\t\t   \033[0;92m[4]\033[0m \033[0;91mLihat Semua Data\033[0m\n");
					printf("\t\t\t\t   \033[0;92m[5]\033[0m \033[0;91mHapus Data\033[0m\n");
					printf("\t\t\t\t   \033[0;92m[6]\033[0m \033[0;91mHapus Semua Data\033[0m\n");
					printf("\n\t\t\t\t   \033[0;92m[0]\033[0m \033[0;91mKembali ke Halaman Awal\033[0m\n");
					
					printf("\n\t\t\t\t   \033[0;92m>> ");
					c1 = scanf("%d%c", &cho1, &nextch1);
					fflush(stdin);
                    printf("\033[0m");
					if(c1 == 0 || nextch1 != '\n'){
						printf("\t\t\t\t   \033[0;92mPilih Angka yang tersedia!\033[0m\n");
						getch();
					}
				}while(c1 == 0 || nextch1 != '\n');
				
				switch(cho1){
					case 1:
						system("cls");
                        judulinsert();
						do{
							strcpy(key, "");
                            printf("\t\t\t\t   \033[0;91mTambahkan Kata Baru : \033[0m\n\t\t\t\t   ");
							scanf(" %26[^\n]", key);
                            fflush(stdin);
							if(strlen(key)> 25){
								printf("\t\t\t\t   \033[0;92mKata tidak boleh >25!\033[0m\n");
								getch();
								system("cls");
                                judulinsert();
							}
						}while(strlen(key) > 25);
						lowerCase(key);
						if(keyExists(root, key)){
							printf("\n\t\t\t\t   \033[0;92mTidak Dapat Menambahkan Data! \033[0m\n");
                            printf("\t\t\t\t   \033[0;92mKata yang Anda Tambahkan telah tersedia!\033[0m\n");
							getch();
							system("cls");
							break;
						}
						do{
							strcpy(kbenda, "");
                            printf("\t\t\t\t   \033[0;91mKata Benda dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
							scanf(" %51[^\n]", kbenda);
                            fflush(stdin);
							if(strlen(kbenda)> 50){
								printf("\t\t\t\t   \033[0;92mKata Benda tidak boleh >50 kata!\033[0m\n");
								getch();
								system("cls");
                                judulinsert();
                                printf("\t\t\t\t   \033[0;91mTambahkan Kata Baru : \033[0m\n\t\t\t\t   %s\n", key);
							}
						}while(strlen(kbenda) > 50);

						do{
							strcpy(kkerja, "");
                            printf("\t\t\t\t   \033[0;91mKata Kerja dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
							scanf(" %51[^\n]", kkerja);
                            fflush(stdin);
                            if(strlen(kkerja)> 50){
								printf("\t\t\t\t   \033[0;92mKata kerja tidak boleh >50 kata!\033[0m\n");
								getch();
								system("cls");
                                judulinsert();
                                printf("\t\t\t\t   \033[0;91mTambahkan Kata Baru : \033[0m\n\t\t\t\t   %s\n", key);
                                printf("\t\t\t\t   \033[0;91mKata Benda dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   %s\n", key, kbenda);
							}
						}while(strlen(kkerja) > 50);

						insert(&root, strdup(key), strdup(kbenda), strdup(kkerja));
						printf("\n\t\t\t\t   \033[0;92mBerhasil Menambahkan Data Baru!\033[0m\n");
						getch();
						system("cls");
						break;
					case 2:
						system("cls");
                        judulupdate();
						tabel(root);
						printf("\n\t\t\t\t   \033[0;91mKata yang akan diperbarui : \033[0m\n\t\t\t\t   ");
						scanf(" %25[^\n]", key);
						lowerCase(key);
				        struct BTreeNode* result = search(root, key);
				        if(result)
				            printf("\n\t\t\t\t   \033[0;92mBerhasil menemukan informasi dari '%s'!\033[0m\n\n", key);
				        else{
				            printf("\n\t\t\t\t   \033[0;92mTidak dapat menemukan kata\033[0m %s\033[0;92m!\033[0m\n", key);
				            getch();
				            system("cls");
				            break;
				        }
				        do{
					        do{
								system("cls");
                                judulupdate();
								printf("\t\t\t\t   \033[0;91mData\033[0m %s \033[0;91myang akan diperbarui:\033[0m\n\n", key);
					            printf("\t\t\t\t   \033[0;92m[1]\033[0m \033[0;91mKata Benda\033[0m\n");
					            printf("\t\t\t\t   \033[0;92m[2]\033[0m \033[0;91mKata Kerja\033[0m\n");
					            printf("\t\t\t\t   \033[0;92m[3]\033[0m \033[0;91mKata Benda dan Kata Kerja\033[0m\n");
					            printf("\t\t\t\t   \033[0;92m[4]\033[0m \033[0;91mBatalkan Operasi\033[0m\n\n");
					            printf("\t\t\t\t   \033[0;92m>> ");
					            cup = scanf("%d%c", &choup, &nextchup);
								fflush(stdin);
                                printf("\033[0m");
								if(cup == 0 || nextchup != '\n'){
									printf("\t\t\t\t   \033[0;92mPilih Angka yang tersedia!\033[0m\n");
									getch();
									system("cls");
								}
							}while(cup == 0 || nextchup != '\n');
							
				            switch(choup){
				            	case 1:
				            		system("cls");
                                    judulupdate();
                                    printf("\t\t\t\t   \033[0;91mMasukkan Kata Benda Baru dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
				            		scanf(" %50[^\n]", kbenda);
                                    fflush(stdin);
				            		updatekbenda(root, key, kbenda);
//				            		printf("Kata benda '%s' berhasil diperbarui!\n", key);
				            		getch();
				            		break;
				            	case 2:
				            		system("cls");
                                    judulupdate();
                                    printf("\t\t\t\t   \033[0;91mMasukkan Kata Kerja Baru dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
									scanf(" %50[^\n]", kkerja);
                                    fflush(stdin);
									printf("\n");
                                    updatekkerja(root, key, kkerja);                                    
//									printf("Kata Kerja '%s' berhasil diperbarui!\n", key);
				            		getch();
									break;
								case 3:
									system("cls");
                                    judulupdate();                                    
                                    printf("\t\t\t\t   \033[0;91mMasukkan Kata Benda Baru dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
				            		scanf(" %50[^\n]", kbenda);
                                    fflush(stdin);
				            		printf("\t\t\t\t   \033[0;91mMasukkan Kata Kerja Baru dari\033[0m %s \033[0;91m: \033[0m\n\t\t\t\t   ", key);
									scanf(" %50[^\n]", kkerja);
                                    fflush(stdin);
                                    printf("\n");
				            		updatekbenda(root, key, kbenda);
									updatekkerja(root, key, kkerja);
//									printf("Kata benda dan kata kerja '%s' berhasil diperbarui!\n", key);
				            		getch();
				            		break;
				            	case 4:
				            		break;
				            	default:
				            		printf("\t\t\t\t   \033[0;92mMohon ketik angka yang tersedia!\033[0m\n");
				            		getch();
				            		break;
			            	}
						}while(choup < 1 || choup > 4);
						break;
					case 3:
						system("cls");
                        judulcari();
						tabel(root);
						printf("\n\t\t\t\t   \033[0;91mKata yang dicari : \033[0m\n\t\t\t\t   ");
						scanf(" %25[^\n]", key);
                        fflush(stdin);
						lowerCase(key);
						searchKey(root, key);
						getch();
						system("cls");
						break;
					case 4:
						system("cls");
                        judulkamus();
						tabel(root);
						getch();
						system("cls");
						break;
					case 5:
						system("cls");
                        judulhapus();
						tabel(root);
						printf("\n\t\t\t\t   \033[0;91mKata yang akan dihapus : \033[0m \n\t\t\t\t   ");
						scanf(" %25[^\n]", key);
                        fflush(stdin);
						lowerCase(key);
						int gagal = 0;
						gagal = hapus(root, key);
						if(gagal == 1){
							printf("\n\t\t\t\t   \033[0;92mTidak Dapat Menemukan Kata\033[0m %s\033[0;92m!\033[0m\n", key);
							getch();
							system("cls");
							break;
						}
						printf("\n\t\t\t\t   \033[0;92mBerhasil Menghapus Data\033[0m\n");
						getch();
						system("cls");
						break;
					case 6:
	    				while(1){
                            do{
								system("cls");
                                judulhapusall();
								printf("\t\t\t\t   \033[0;91mAnda yakin ingin menghapus semua data kamus?\033[0m\n\n");
			    				printf("\t\t\t\t   \033[0;92m[1]\033[0m \033[0;91mYa\033[0m\n");
			    				printf("\t\t\t\t   \033[0;92m[2]\033[0m \033[0;91mTidak\n\n");
			    				printf("\t\t\t\t   \033[0;92m>> ");
			    				cdel = scanf("%d%c", &chodel, &nextchdel);
                                printf("\033[0m");
								fflush(stdin);
								if(cdel == 0 || nextchdel != '\n'){
									printf("\t\t\t\t   \033[0;92mPilih Angka yang tersedia!\033[0m\n");
									getch();
								}
							}while(cdel == 0 || nextchdel != '\n');
							
		    				if(chodel == 1){
		    					deleteAll(root);
		    					root = createNode();
		    					printf("\t\t\t\t   \033[0;92mBerhasil Menghapus Semua Data Kamus!\033[0m\n");
		    					getch();
		    					break;
		    				}
		    				else if(chodel == 2){
								printf("\t\t\t\t   \033[0;92mMengurungkan proses penghapusan data!\033[0m\n\n");
								getch();
			    				break;
							}
							else{
								printf("\t\t\t\t   \033[0;92mMohon ketik angka yang tersedia!\033[0m\n");
								getch();
							}
						}
	    			case 0:
	    				break;
	    			default:
	    				printf("\t\t\t\t   \033[0;92mMohon ketik angka yang tersedia!\033[0m\n");
	    				getch();
	    				system("cls");
						break;    				
				}
			
			}while(cho1 != 0);
		}
		
		else if(cho == 2){
			do{
				do{
				system("cls");
                judulkamus();
				printf("\t\t\t\t   \033[0;92m[1]\033[0m \033[0;91mTampilkan Semua Kata\033[0m\n");
				printf("\t\t\t\t   \033[0;92m[2]\033[0m \033[0;91mCari Kata\033[0m\n");
				printf("\n\t\t\t\t   \033[0;92m[0]\033[0m \033[0;91mKembali ke Halaman Awal\033[0m\n");
				
				printf("\n\t\t\t\t   \033[0;92m>> ");
				c2 = scanf("%d%c", &cho2, &nextch2);
				fflush(stdin);
                printf("\033[0m");
					if(c2 == 0 || nextch2 != '\n'){
						printf("\t\t\t\t   \033[0;92mPilih Angka yang tersedia!\033[0m\n");
						getch();
						system("cls");
					}
				}while(c2 == 0 || nextch2 != '\n');
				
				switch(cho2){
					case 1:
						system("cls");
                        judulkamus();
						tabel(root);
						getch();
						system("cls");
						break;
					case 2:
                        system("cls");
                        judulcari();
						printf("\t\t\t\t   \033[0;91mKata yang dicari : \033[0m");
						scanf(" %25[^\n]", key);
                        fflush(stdin);
						lowerCase(key);
						searchKey(root, key);
						getch();
						system("cls");
						break;
					case 0:
						break;
					default:
						printf("\t\t\t\t   \033[0;92mMohon ketik angka yang tersedia!\033[0m\n");
						getch();
						system("cls");
						break;
				}
			}while(cho2 != 0);
		}
		
		else if(cho==0){
			deleteAll(root);
            printf("\n\t\t\t\t   \033[0;92mAnda Telah Keluar dari Kamus!\033[0m\n");
        }
		else{
			printf("\t\t\t\t   \033[0;92mMohon Ketik Angka yang Tersedia!\033[0m\n");
			getch();
		}
		
	}while(cho!=0);
	
	return 0;
}

void readFile(struct BTreeNode** root){
    FILE* fp;
	fp = fopen("data.txt", "r");
    if(fp == NULL){
        judulkamus();
        printf("\n\t\t\t\t   \033[0;91mTidak dapat menemukan data file\033[0m\n");
        getch();
        exit(1);
    }
    char keyy[25];
    char kbendaa[50];
    char kkerjaa[50];

    while(fscanf(fp, "%[^\';'];%[^\';'];%[^\n]\n", keyy, kbendaa, kkerjaa) != EOF){
        insert(root, strdup(keyy), strdup(kbendaa), strdup(kkerjaa));
    }

    fclose(fp);
}

void lowerCase(char* str){
    for (int i = 0; str[i] != '\0'; i++){
        str[i] = tolower(str[i]);
    }
}

void tabel(struct BTreeNode* root){
	printf("\n\033[0;91m=======================================================================================================================================\033[0m\n");
	printf("| \033[0;91mKATA\033[0m\t\t\t    | \033[0;91mKATA BENDA\033[0m\t\t\t\t\t | \033[0;91mKATA KERJA\033[0m\t\t\t\t              |\n");
	printf("\033[0;91m=======================================================================================================================================\033[0m\n");
	display(root);
	printf("\033[0;91m=======================================================================================================================================\033[0m\n");
}

void judulkamus(){
    printf("\033[1;94m"); 
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t       Kamus Bahasa Indonesia\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void juduladmin(){
    printf("\033[1;94m"); 
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t\t    Halaman Admin\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void judulinsert(){
    printf("\033[1;94m");
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t         Sisipkan Data Baru\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void judulupdate(){
    printf("\033[1;94m");
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t           Perbarui Data\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void judulcari(){
    printf("\033[1;94m");
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t             Cari Kata\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void judulhapus(){
    printf("\033[1;94m");
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t             Hapus Data\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

void judulhapusall(){
    printf("\033[1;94m");
    printf("\t\t\t\t   ______________________________\n\n");
    printf("\t\t\t\t          Hapus Semua Data\n");
    printf("\t\t\t\t   ______________________________\n\n\n");
    printf("\033[0m");
}

bool adminlogin(){
    int plength = 10;
    char pass[plength +1], user[11];
    
    for(int limax = 0; limax<5; limax++){
        int p = 0;
        char ch;
        printf("\t\t\t\t   \033[0;91mUsername : \033[0m");
        scanf(" %10[^\n]", user);
        fflush(stdin);
        printf("\t\t\t\t   \033[0;91mPassword : \033[0m");

        while ((ch = _getch()) != '\r') {
            if (ch == 8 || ch == 127){
                if (p > 0){
                    p--;
                    printf("\b \b");
                }
            }
            else if (p < plength){
                pass[p++] = ch;
                printf("*");
            }
        }
        pass[p] = '\0';

        if(strcmp(pass,"pass")==0 && strcmp(user,"user")==0){
            printf("\n\t\t\t\t   \033[0;92mPassword berhasil dimasukkan!\033[0m\n");
            system("cls");
            return true;
            break;
        }
        else{
            printf("\n\n\t\t\t\t   \033[0;92mUsername atau Password salah!\033[0m\n");
            getch();
            system("cls");
            juduladmin();
        }
    }
    printf("\t\t\t\t   \033[0;92mAnda telah salah memasukkan Password 5x\033[0m\n");
    printf("\t\t\t\t   \033[0;92mMengembalikan ke Halaman Awal!\033[0m\n");
    return false;
}

void display(struct BTreeNode* node){
    int i;
	if (node != NULL){
        for (i = 0; i < node->numKeys; i++){
            if (!node->isLeaf)
                display(node->children[i]);
            printf("| \033[0;94m%-25s\033[0m | \033[0;94m%-50s\033[0m | \033[0;94m%-50s\033[0m |\n", node->keys[i], node->kbenda[i], node->kkerja[i]);
        }

        if (!node->isLeaf)
            display(node->children[i]);
    }
    if(i==0){
    	printf("\n\t\t\t\t \033[0;91mBelum ada Kata tersedia!\033[0m\n");
    	return;
	}
}

bool keyExists(struct BTreeNode* node, char* key){
    int i;
    for (i = 0; i < node->numKeys; i++){
        int comparison = strcmp(key, node->keys[i]);
        if (comparison == 0){
            return true;
        }
		else if (comparison < 0){
            if (node->isLeaf)
                break;
            else
                return keyExists(node->children[i], key);
        }
    }

    if (node->isLeaf)
        return false;
    else
        return keyExists(node->children[i], key);
}

struct BTreeNode* createNode(){
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->numKeys = 0;
    newNode->keys = (char**)malloc((2 * MIN_DEGREE - 1) * sizeof(char*));
    newNode->kbenda = (char**)malloc((2 * MIN_DEGREE - 1) * sizeof(char*));
    newNode->kkerja = (char**)malloc((2 * MIN_DEGREE - 1) * sizeof(char*));
    newNode->children = (struct BTreeNode**)malloc(2 * MIN_DEGREE * sizeof(struct BTreeNode*));
    newNode->isLeaf = 1;
    return newNode;
}

void insert(struct BTreeNode** root, char* key, char* kbenda, char* kkerja){
    struct BTreeNode* rootNode = *root;

    if (rootNode->numKeys == (2 * MIN_DEGREE) - 1){
        struct BTreeNode* newRoot = createNode();
        newRoot->isLeaf = 0;
        newRoot->children[0] = rootNode;
        *root = newRoot;
        splitChild(newRoot, 0);
        insertNonFull(newRoot, key, kbenda, kkerja);
    }
	else{
        insertNonFull(rootNode, key, kbenda, kkerja);
    }
}

void splitChild(struct BTreeNode* parentNode, int childIndex){
    struct BTreeNode* childNode = parentNode->children[childIndex];
    struct BTreeNode* rightChildNode = createNode();

    rightChildNode->isLeaf = childNode->isLeaf;
    rightChildNode->numKeys = MIN_DEGREE - 1;

    for(int j = 0; j < MIN_DEGREE - 1; j++){
        rightChildNode->keys[j] = childNode->keys[j + MIN_DEGREE];
        rightChildNode->kbenda[j] = childNode->kbenda[j + MIN_DEGREE];
        rightChildNode->kkerja[j] = childNode->kkerja[j + MIN_DEGREE];
        childNode->keys[j + MIN_DEGREE] = NULL;
        childNode->kbenda[j + MIN_DEGREE] = NULL;
        childNode->kkerja[j + MIN_DEGREE] = NULL;
    }

    if (!childNode->isLeaf){
        for (int j = 0; j < MIN_DEGREE; j++){
            rightChildNode->children[j] = childNode->children[j + MIN_DEGREE];
            childNode->children[j + MIN_DEGREE] = NULL;
        }
    }

    childNode->numKeys = MIN_DEGREE - 1;

    for (int j = parentNode->numKeys; j > childIndex; j--)
        parentNode->children[j + 1] = parentNode->children[j];

    parentNode->children[childIndex + 1] = rightChildNode;

    for (int j = parentNode->numKeys - 1; j >= childIndex; j--){
        parentNode->keys[j + 1] = parentNode->keys[j];
        parentNode->kbenda[j + 1] = parentNode->kbenda[j];
        parentNode->kkerja[j + 1] = parentNode->kkerja[j];
    }

    parentNode->keys[childIndex] = childNode->keys[MIN_DEGREE - 1];
    parentNode->kbenda[childIndex] = childNode->kbenda[MIN_DEGREE - 1];
    parentNode->kkerja[childIndex] = childNode->kkerja[MIN_DEGREE - 1];
    childNode->keys[MIN_DEGREE - 1] = NULL;
    childNode->kbenda[MIN_DEGREE - 1] = NULL;
    childNode->kkerja[MIN_DEGREE - 1] = NULL;
    parentNode->numKeys++;
}

void insertNonFull(struct BTreeNode* node, char* key, char* kbenda, char* kkerja){
    int index = node->numKeys - 1;

    if (node->isLeaf){
        while (index >= 0 && strcmp(key, node->keys[index]) < 0){
            node->keys[index + 1] = node->keys[index];
            node->kbenda[index + 1] = node->kbenda[index];
            node->kkerja[index + 1] = node->kkerja[index];
            index--;
        }
		
//		if (index >= 0 && strcmp(key, node->keys[index]) == 0){
//            printf("'%s' already exists\n", key);
//            return;
//        }
        
        node->keys[index + 1] = key;
        node->kbenda[index + 1] = kbenda;
        node->kkerja[index + 1] = kkerja;
        node->numKeys++;
    }
	else{
        while (index >= 0 && strcmp(key, node->keys[index]) < 0)
            index--;
//		if (index >= 0 && strcmp(key, node->keys[index]) == 0){
//            printf("'%s' already exists\n", key);
//            return;
//        }
        index++;
        struct BTreeNode* childNode = node->children[index];
        if (childNode->numKeys == (2 * MIN_DEGREE) - 1){
            splitChild(node, index);
            if (strcmp(key, node->keys[index]) > 0)
                index++;
        }
        insertNonFull(node->children[index], key, kbenda, kkerja);
    }
}

int hapus(struct BTreeNode* node, char* key){
    int index = 0;
    while (index < node->numKeys && strcmp(key, node->keys[index]) > 0)
        index++;

    if (index < node->numKeys && strcmp(node->keys[index], key) == 0){
        if (node->isLeaf){
            for (int i = index; i < node->numKeys - 1; i++){
                node->keys[i] = node->keys[i + 1];
                node->kbenda[i] = node->kbenda[i + 1];
                node->kkerja[i] = node->kkerja[i + 1];
            }
            node->keys[node->numKeys - 1] = NULL;
            node->kbenda[node->numKeys - 1] = NULL;
            node->kkerja[node->numKeys - 1] = NULL;
            node->numKeys--;
        }
		else{
            struct BTreeNode* predecessorChild = node->children[index];
            struct BTreeNode* successorChild = node->children[index + 1];

            if (predecessorChild->numKeys >= MIN_DEGREE){
                char* predecessorKey = predecessorChild->keys[predecessorChild->numKeys - 1];
                char* predecessorkbenda = predecessorChild->kbenda[predecessorChild->numKeys - 1];
                char* predecessorkkerja = predecessorChild->kkerja[predecessorChild->numKeys - 1];
                hapus(predecessorChild, predecessorKey);
                node->keys[index] = predecessorKey;
                node->kbenda[index] = predecessorkbenda;
                node->kkerja[index] = predecessorkkerja;
            }
			else if (successorChild->numKeys >= MIN_DEGREE){
                char* successorKey = successorChild->keys[0];
                char* successorkbenda = successorChild->kbenda[0];
                char* successorkkerja = successorChild->kkerja[0];
                hapus(successorChild, successorKey);
                node->keys[index] = successorKey;
                node->kbenda[index] = successorkbenda;
                node->kkerja[index] = successorkkerja;
            }
			else{
                mergeChildren(node, index);
                hapus(predecessorChild, key);
            }
        }
    }
	else{
        if (node->isLeaf){
//            printf("Tidak Dapat Menemukan Kata '%s'\n", key);
            return 1;
        }

        struct BTreeNode* childNode = node->children[index];
        if (childNode->numKeys == MIN_DEGREE - 1){
            struct BTreeNode* leftSibling = (index > 0) ? node->children[index - 1] : NULL;
            struct BTreeNode* rightSibling = (index < node->numKeys) ? node->children[index + 1] : NULL;

            if (leftSibling && leftSibling->numKeys >= MIN_DEGREE){
                borrowFromLeftSibling(node, index);
            }
			else if (rightSibling && rightSibling->numKeys >= MIN_DEGREE){
                borrowFromRightSibling(node, index);
            }
			else{
                if(leftSibling){
                    mergeChildren(node, index - 1);
                    childNode = leftSibling;
                }
				else{
                    mergeChildren(node, index);
                }
            }
        }
        hapus(childNode, key);
    }
}

void mergeChildren(struct BTreeNode* node, int index){
    struct BTreeNode* leftChild = node->children[index];
    struct BTreeNode* rightChild = node->children[index + 1];

    leftChild->keys[leftChild->numKeys] = node->keys[index];
    leftChild->kbenda[leftChild->numKeys] = node->kbenda[index];
    leftChild->kkerja[leftChild->numKeys] = node->kkerja[index];
    leftChild->numKeys++;

    for (int i = 0; i < rightChild->numKeys; i++){
        leftChild->keys[leftChild->numKeys] = rightChild->keys[i];
        leftChild->kbenda[leftChild->numKeys] = rightChild->kbenda[i];
        leftChild->kkerja[leftChild->numKeys] = rightChild->kkerja[i];
        leftChild->numKeys++;
    }

    if (!leftChild->isLeaf){
        for (int i = 0; i <= rightChild->numKeys; i++)
            leftChild->children[leftChild->numKeys + i] = rightChild->children[i];
    }

    for (int i = index; i < node->numKeys - 1; i++){
        node->keys[i] = node->keys[i + 1];
        node->kbenda[i] = node->kbenda[i + 1];
        node->kkerja[i] = node->kkerja[i + 1];
        node->children[i + 1] = node->children[i + 2];
    }

    node->keys[node->numKeys - 1] = NULL;
    node->kbenda[node->numKeys - 1] = NULL;
    node->kkerja[node->numKeys - 1] = NULL;
    node->children[node->numKeys] = NULL;

    node->numKeys--;
    free(rightChild->keys);
    free(rightChild->kbenda);
    free(rightChild->kkerja);
    free(rightChild->children);
    free(rightChild);
}

void borrowFromLeftSibling(struct BTreeNode* node, int index){
    struct BTreeNode* childNode = node->children[index];
    struct BTreeNode* leftSibling = node->children[index - 1];

    for (int i = childNode->numKeys; i > 0; i--){
        childNode->keys[i] = childNode->keys[i - 1];
        childNode->kbenda[i] = childNode->kbenda[i - 1];
        childNode->kkerja[i] = childNode->kkerja[i - 1];
    }

    if (!childNode->isLeaf){
        for (int i = childNode->numKeys + 1; i > 0; i--)
            childNode->children[i] = childNode->children[i - 1];
        childNode->children[0] = leftSibling->children[leftSibling->numKeys];
    }

    childNode->keys[0] = node->keys[index - 1];
    childNode->kbenda[0] = node->kbenda[index - 1];
    childNode->kkerja[0] = node->kkerja[index - 1];

    node->keys[index - 1] = leftSibling->keys[leftSibling->numKeys - 1];
    node->kbenda[index - 1] = leftSibling->kbenda[leftSibling->numKeys - 1];
    node->kkerja[index - 1] = leftSibling->kkerja[leftSibling->numKeys - 1];

    childNode->numKeys++;
    leftSibling->numKeys--;
}

void borrowFromRightSibling(struct BTreeNode* node, int index){
    struct BTreeNode* childNode = node->children[index];
    struct BTreeNode* rightSibling = node->children[index + 1];

    childNode->keys[childNode->numKeys] = node->keys[index];
    childNode->kbenda[childNode->numKeys] = node->kbenda[index];
    childNode->kkerja[childNode->numKeys] = node->kkerja[index];
    childNode->numKeys++;

    node->keys[index] = rightSibling->keys[0];
    node->kbenda[index] = rightSibling->kbenda[0];
    node->kkerja[index] = rightSibling->kkerja[0];

    for (int i = 0; i < rightSibling->numKeys - 1; i++){
        rightSibling->keys[i] = rightSibling->keys[i + 1];
        rightSibling->kbenda[i] = rightSibling->kbenda[i + 1];
        rightSibling->kkerja[i] = rightSibling->kkerja[i + 1];
    }

    if (!rightSibling->isLeaf){
        childNode->children[childNode->numKeys] = rightSibling->children[0];
        for (int i = 0; i < rightSibling->numKeys; i++)
            rightSibling->children[i] = rightSibling->children[i + 1];
    }

    rightSibling->numKeys--;
}

void updatekbenda(struct BTreeNode* node, char* key, char* newkbenda){
    int i;
    for (i = 0; i < node->numKeys; i++){
        int comparison = strcmp(key, node->keys[i]);
        if (comparison == 0){
            free(node->kbenda[i]);
			node->kbenda[i] = strdup(newkbenda);
            printf("\t\t\t\t   \033[0;92mKata benda dari\033[0m %s \033[0;92mberhasil diperbarui!\033[0m\n", key);
            return;
        }
		else if (comparison < 0){
            if (node->isLeaf)
                break; 
            else{
                updatekbenda(node->children[i], key, newkbenda);
                return;
            }
        }
    }
    if (node->isLeaf)
        printf("\t\t\t\t   \033[0;92mTidak dapat menemukan kata\033[0m %s\033[0;92m!\033[0m\n", key);
    else
        updatekbenda(node->children[i], key, newkbenda);
}

void updatekkerja(struct BTreeNode* node, char* key, char* newkkerja){
    int i;
    for (i = 0; i < node->numKeys; i++){
        int comparison = strcmp(key, node->keys[i]);
        if (comparison == 0){
            free(node->kkerja[i]);
            node->kkerja[i] = strdup(newkkerja);
            printf("\t\t\t\t   \033[0;92mKata kerja dari\033[0m %s \033[0;92mberhasil diperbarui!\033[0m\n", key);
            return;
        }
        else if (comparison < 0){
            if (node->isLeaf)
                break;
            else{
                updatekkerja(node->children[i], key, newkkerja);
                return;
            }
        }
    }
    if (node->isLeaf)
        printf("\t\t\t\t   \033[0;92mTidak dapat menemukan kata\033[0m %s\033[0;92m!\033[0m\n", key);
    else
        updatekkerja(node->children[i], key, newkkerja);
}

struct BTreeNode* search(struct BTreeNode* node, char* key){
    int i = 0;
    while (i < node->numKeys && strcmp(key, node->keys[i]) > 0)
        i++;

    if (i < node->numKeys && strcmp(key, node->keys[i]) == 0)
        return node;

    if (node->isLeaf)
        return NULL;

    return search(node->children[i], key);
}

void searchKey(struct BTreeNode* node, char* key){
    int i;
    for (i = 0; i < node->numKeys; i++){
        int comparison = strcmp(key, node->keys[i]);
        if (comparison == 0){
            // printf("\n\t\t\t\t\t\t   %s\n\n", node->keys[i]);
            printf("\t\t\t\t   \033[0;92mKata Benda :\033[0m %s\n", node->kbenda[i]);
            printf("\t\t\t\t   \033[0;92mKata Kerja :\033[0m %s\n", node->kkerja[i]);
            return;
        }
		else if (comparison < 0){
            if (node->isLeaf)
                break;
            else{
                searchKey(node->children[i], key);
                return;
            }
        }
    }

    if (node->isLeaf)
        printf("\t\t\t\t   \033[0;92mTidak dapat menemukan kata\033[0m %s\033[0;92m!\033[0m\n", key);
    else
        searchKey(node->children[i], key);
}

void deleteAll(struct BTreeNode* node){
    if (node == NULL)
        return;

    if (node->isLeaf){
        for(int i = 0; i < node->numKeys; i++){
            free(node->keys[i]);
            free(node->kbenda[i]);
            free(node->kkerja[i]);
        }
    }
	else{
        for (int i = 0; i < node->numKeys + 1; i++){
            deleteAll(node->children[i]);
        }
    }

    free(node);
}

/*
halaman awal
1. admin(password included):
	1. Insert
	2. Update : 
		1. update data1 only
		2. update data2 only
		3. update all data
	3. Search
	4. View all data
	5. Delete
	6. Delete all data : anda yakin akan menghapus semua data
	7. Exit

2. user:
	1. view all data
	2. search
	3. Exit

*/