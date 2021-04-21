    #include "mbed.h"              
    #include <stdio.h>
    #include "SDFileSystem.h"
    #include "PinDetect.h"

    DigitalOut rA(p20);
    DigitalOut rB(p19);
    DigitalOut rC(p18);
    DigitalOut r1(p17);
    DigitalOut r2(p16);
    DigitalOut cA(p10);
    DigitalOut cB(p9);
    DigitalOut cC(p8);
    DigitalOut c1(p7);
    DigitalOut c2(p6);
    DigitalOut rIn(p15);
    DigitalOut cIn(p5);
    DigitalOut myled(LED1);

    Serial pc(USBTX, USBRX); // tx, rx
    SDFileSystem sdCard(p11,p12,p13,p14, "sd");
    PinDetect button(p21);

    int led_out[3][4] = {
            {1, 1, 1, 1},
            {1, 1, 1, 1},
            {1, 1, 1, 1}
            };
    int cursorPosition = -1;
    char text[1000];
    struct lut {
        int cell[3][2];
    } lut[66];
    char ch;
    FILE * f;

    int r[3];
    int c[3];

    void decToBinary(int n, int which) {
        int i = 0;
        while (n > 0) {
            if (which == 0) {
                r[i] = n % 2;
            } else {
                c[i] = n % 2;
            } 
            n = n / 2; 
            i++;
        }
        return;
    }

    void populate_LUT() {
        pc.printf("opening lut.bin with write access....");
        f = fopen("/sd/mydir/lut.bin", "w");
        pc.printf("done.\n");
        pc.printf("Making the lookup table...");
        int lut[66][3][2] = {
                                {  
                                    {0, 0},
                                    {0, 0},
                                    {0, 0}
                                },

                                {
                                    {0, 1},
                                    {1, 0},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 1},
                                    {0, 0}
                                },

                                {
                                    {0, 1},
                                    {0, 1},
                                    {1, 1}
                                },

                                {       
                                    {1, 1},
                                    {1, 0},
                                    {0, 1}
                                },

                                {           
                                    {1, 1},
                                    {0, 0},
                                    {0, 1}
                                },

                                {       
                                    {1, 1},
                                    {1, 0},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 0},
                                    {1, 0}
                                },

                                {       
                                    {1, 0},
                                    {1, 1},
                                    {1, 1}
                                },

                                {
                                    {0, 1},
                                    {1, 1},
                                    {1, 1}
                                },

                                {
                                    {1, 0},
                                    {0, 0},
                                    {0, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 0},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 0},
                                    {0, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 0},
                                    {1, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 0},
                                    {0, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 0},
                                    {1, 0}
                                },

                                {
                                    {0, 0},
                                    {0, 1},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {1, 0},
                                    {0, 0}
                                },

                                {
                                    {0, 0},
                                    {1, 0},
                                    {1, 0}
                                },

                                {
                                    {0, 0},
                                    {1, 1},
                                    {0, 0}
                                },

                                {
                                    {0, 0},
                                    {1, 1},
                                    {0, 1}
                                },

                                {
                                    {0, 0},
                                    {1, 0},
                                    {0, 1}
                                },

                                {
                                    {0, 0},
                                    {1, 1},
                                    {1, 0}
                                },

                                {
                                    {0, 0},
                                    {1, 1},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {1, 0},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 1},
                                    {1, 0}
                                },

                                {
                                    {1, 0},
                                    {0, 1},
                                    {0, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 1},
                                    {0, 1}
                                },

                                {
                                    {1, 0},
                                    {1, 0},
                                    {0, 1}
                                },

                                {
                                    {1, 1},
                                    {1, 1},
                                    {1, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 1},
                                    {1, 0}
                                },

                                {
                                    {1, 1},
                                    {0, 1},
                                    {0, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 0},
                                    {0, 0}
                                },

                                {
                                    {0, 1},
                                    {1, 0},
                                    {0, 1}
                                },

                                {
                                    {1, 0},
                                    {1, 1},
                                    {0, 1}
                                },

                                {
                                    {1, 1},
                                    {1, 1},
                                    {0, 1}
                                },

                                {
                                    {0, 1},
                                    {0, 1},
                                    {0, 0}
                                },

                                {
                                    {0, 1},
                                    {0, 1},
                                    {0, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 0},
                                    {0, 0}
                                },

                                {
                                    {1, 0},
                                    {0, 0},
                                    {0, 0}
                                },

                                { 
                                    {1, 0},
                                    {1, 0},
                                    {0, 0}
                                },

                                { 
                                    {1, 1},
                                    {0, 0},
                                    {0, 0}
                                },

                                {
                                    {1, 1},
                                    {0, 1},
                                    {0, 0}
                                },

                                {
                                    {1, 0},
                                    {0, 1},
                                    {0, 0}
                                },

                                {
                                    {1, 1},
                                    {1, 0},
                                    {0, 0}
                                },

                                {
                                    {1, 1},
                                    {1, 1},
                                    {0, 0}
                                },

                                {
                                    {1, 0},
                                    {1, 1},
                                    {0, 0}
                                },

                                { 
                                    {0, 1},
                                    {1, 0},
                                    {0, 0}
                                },

                                { 
                                    {0, 1},
                                    {1, 1},
                                    {0, 0}
                                },

                                { 
                                    {1, 0},
                                    {0, 0},
                                    {1, 0}
                                },

                                { 
                                    {1, 0},
                                    {1, 0},
                                    {1, 0}
                                },

                                { 
                                    {1, 1},
                                    {0, 0},
                                    {1, 0}
                                },

                                { 
                                    {1, 1},
                                    {0, 1},
                                    {1, 0}
                                },

                                { 
                                    {1, 0},
                                    {0, 1},
                                    {1, 0}
                                },

                                { 
                                    {1, 1},
                                    {1, 0},
                                    {1, 0}
                                },

                                { 
                                    {1, 1},
                                    {1, 1},
                                    {1, 0}
                                },

                                { 
                                    {1, 0},
                                    {1, 1},
                                    {1, 0}
                                },

                                { 
                                    {0, 1},
                                    {1, 0},
                                    {1, 0}
                                },

                                {
                                    {0, 1},
                                    {1, 1},
                                    {1, 0}
                                },

                                { 
                                    {1, 0},
                                    {0, 0},
                                    {1, 1}
                                },

                                { 
                                    {1, 0},
                                    {1, 0},
                                    {1, 1}
                                },

                                { 
                                    {0, 1},
                                    {1, 1},
                                    {0, 1}
                                },

                                { 
                                    {1, 1},
                                    {0, 0},
                                    {1, 1}
                                },

                                { 
                                    {1, 1},
                                    {0, 1},
                                    {1, 1}
                                },

                                {
                                    {1, 0},
                                    {0, 1},
                                    {1, 1}
                                },

                                {
                                    {0, 0},
                                    {0, 1},
                                    {1, 1}
                                }

                            };
        //SPACE lut[0] 
        //! lut[1][0]
        //" lut[2]
        //# lut[3]
        //$ lut[4]      
        //% lut[5]          
        //& lut[6]      
        //' lut[7]
        //( lut[8]      
        //) lut[9]
        //* lut[10]
        //+ lut[11]
        //,lut[12]
        //- lut[13]
        //. lut[14]
        // /    lut[15]
        //0 lut[16]
        //1     lut[17]
        //2 lut[18]
        //3 lut[19]
        //4 lut[20]
        //5 lut[21]
        //6 lut[22]
        //7 lut[23]
        //8 lut[24]
        //9 lut[25]
        // :    lut[26]
        // ;    lut[27]
        //< lut[28]
         //=    lut[29]
        //> lut[30]
        //? lut[31]
        //@ lut[32]
        //[ lut[33]
        //\ lut[34]
        //] lut[35]
        //^ lut[36]
        //_ lut[37]
        //a lut[39]
        //b lut[40] 
        //c lut[41] 
        //d lut[42]
        //e lut[43]
        //f lut[44]
        //g lut[45]
        //h lut[46]
        //i lut[47] 
        //j lut[48] 
        //k lut[49] 
        //l lut[50] 
        //m lut[51] 
        //n lut[52] 
        //o lut[53] 
        //p lut[54] 
        //q lut[55] 
        //r lut[56] 
        //s lut[57] 
        //t lut[58]
        //u lut[59] 
        //v lut[60] 
        //w lut[61] 
        //x lut[62] 
        //y lut[63] 
        //z lut[64]
        pc.printf("done.\n");
        pc.printf("writing to file...");
        fwrite(lut, sizeof(lut), 1, f);
        fclose(f);
        pc.printf("done.\n");
        return;
    }
    void scroll(){
        cursorPosition += 1;   
    }

    void print_braille_output() {
        cursorPosition++;
        ch = text[cursorPosition];
        char ascii_vals[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
        for (int i = 0; i < 8; i++) {
            ascii_vals[i] = fgetc(f);   
        }
        int cells[8][3][2] = {{{1, 1}, {1, 1}, {1, 1}}, 
                              {{1, 1}, {1, 1}, {1, 1}}, 
                              {{1, 1}, {1, 1}, {1, 1}}, 
                              {{1, 1}, {1, 1}, {1, 1}}, 
                              {{1, 1}, {1, 1}, {1, 1}}, 
                              {{1, 1}, {1, 1}, {1, 1}},
                              {{1, 1}, {1, 1}, {1, 1}},
                              {{1, 1}, {1, 1}, {1, 1}}};   


        char ascii_val;
        for (int char_no = 0; char_no < 8; char_no++) {

            ascii_val = ascii_vals[char_no];

            if (ascii_val < 32) {
                //printf("not a valid char.\n");
            } else if (ascii_val < 65) {
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        cells[char_no][i][j] = lut[ascii_val - 32].cell[i][j];
                    }
                }
                
            } else if (ascii_val < 91) {
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        cells[char_no][i][j] = lut[ascii_val - 26].cell[i][j];
                    }
                }
                
            } else if (ascii_val == 96) {
                
                //printf("not a valid char.\n");
                
            } else if (ascii_val > 122) {
                
                //printf("not a valid char.\n");
                
            } else {
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 2; j++) {
                        cells[char_no][i][j] = lut[ascii_val - 58].cell[i][j];
                    }
                }
            }
        }
        
        // print array representation
        char chars[8][6];
        char char1[6];
        char char2[6];

        for (int char_no = 0; char_no < 4; char_no++) {
            printf("%c ", ascii_vals[char_no]);
            for (int i = 0; i < 3; i++) {
                //pc.printf("|");
                for (int j = 0; j < 2; j++) {
                    // led_out[i][j] = cell[i][j];
                    // led_out[i][j + 2] = cell2[i][j];
                    if (cells[char_no][i][j]) {
                        chars[char_no][2*i + j] = '*';
                    } else {
                        chars[char_no][2*i + j] = '.';
                    }
                }
                //printf("\n");
            }
            for (int i = 0; i < 6; i++) {
                    printf("%c", chars[char_no][i]);   
            }
            printf(" | ");
        }
        printf("\n");
        wait(0.05);
        for (int char_no = 4; char_no < 8; char_no++) {
            printf("%c ", ascii_vals[char_no]);
            for (int i = 0; i < 3; i++) {
                //pc.printf("|");
                for (int j = 0; j < 2; j++) {
                    //led_out[i][j] = cell[i][j];
                    //led_out[i][j + 2] = cell2[i][j];
                    if (cells[char_no][i][j]) {
                        chars[char_no][2*i + j] = '*';
                    } else {
                        chars[char_no][2*i + j] = '.';
                    }
                }
                //printf("\n");
            }
            for (int i = 0; i < 6; i++) {
                    printf("%c", chars[char_no][i]);   
            }
            printf(" | ");
        }
        printf("\n\n");
    }
     
    int main() { 
        int ascii_val;
        mkdir("/sd/mydir/", 0777);
        f = fopen("/sd/mydir/lut.bin", "r");
        
         // attach the address of the flip function to the rising edge
        button.mode(PullUp);
        button.attach_deasserted(&print_braille_output);
        button.setSampleFrequency();
        if (f == NULL){
            // fclose(f);
            pc.printf("Making LUT...");
            populate_LUT();
            pc.printf("done.\n");
            f = fopen("lut.bin", "r");
        } else {
            pc.printf("LUT already populated.\n");
        }
        pc.printf("reading lookup table...\n");
        fread(lut, sizeof(int), 66 * 3 * 2, f);
        fclose(f);
        pc.printf("Opening test string.\n");
        f = fopen("/sd/mydir/test.txt", "r");
        pc.printf("Text file scanned.\n");
            
        r1 = 0;
        r2 = 0;
        c1 = 0;
        c2 = 0;
        
        myled = 1;
        wait(0.2);
        myled = 0;
        wait(0.2);
        
         while(1) {
             for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    
                    for (int a = 0; a < 3; a++) {
                        r[a] = 0;
                    }

                    for (int a = 0; a < 4; a++) {
                        c[a] = 0;
                    }
                    
                    // convert row to binary and send to r
                    decToBinary(i, 0);
                    rA = r[0];
                    rB = r[1];
                    rC = r[2];
                    // convert col to binary and send to c
                    decToBinary(j, 1);
                    cA = c[0];
                    cB = c[1];
                    cC = c[2];
                    // send led_out[i][j] to rIn and cIn
                    if (led_out[i][j] == 1) {
                        rIn = 1;
                        cIn = 1;
                    } else {
                        rIn = 0;
                        cIn = 0;
                    }
                    wait(.001);
                }
            }
        }
        return 0;
    }
