/*
 * STL Converter
 *
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 *
 * STL -> Arduino PROGMEM + ArduinoGL
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void badStl(void) {
    
    fprintf(stderr, "Bad STL file\n");
    exit(1);
}

int main(int argc, char * argv[]) {
    
    if(argc < 2) {
        
        fprintf(stderr, "Use: %s <stl file> [output ArduinoGL C file]\n", argv[0]);
        fprintf(stderr, "Example: %s model.stl\n", argv[0]);
        fprintf(stderr, "Example: %s model.stl output.c\n", argv[0]);
        return 1;
    }
    
    FILE * stl = fopen(argv[1], "r");
    
    if(!stl) {
        
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    FILE * output = NULL;
    
    if(argc >= 3) {
        
        output = fopen(argv[2], "w");
        
        if(!output) {
            
            fprintf(stderr, "Cannot write fo file %s\n", argv[2]);
            return 1;
        }
    }
    
    char header[81];
    
    if(fread(header, sizeof(char), 80, stl) < 80) {
        
        badStl();
    }
    
    header[80] = '\0';
    printf("STL header: %s\n", header);
    
    uint32_t nFacets;
    
    if(fread(&nFacets, sizeof(uint32_t), 1, stl) < 1) {
        
        badStl();
    }
    
    printf("%u facets\n", nFacets);

    if(output) {
        
        fprintf(output, "/* %s */\n\n", argv[1]);
        fprintf(output, "#include <avr/pgmspace.h>\n\n");
        fprintf(output, "const float model[%u] PROGMEM = {", nFacets * 9);
    }
    
    for(unsigned i = 0; i < nFacets; i++) {
        
        float normal[3];
        float v1[3], v2[3], v3[3];
        uint16_t byteCount;
        
        printf("Face %u\n", i);
        
        if(fread(normal, sizeof(float), 3, stl) < 3)
            badStl();
        
        if(fread(v1, sizeof(float), 3, stl) < 3)
            badStl();
        
        if(fread(v2, sizeof(float), 3, stl) < 3)
            badStl();
        
        if(fread(v3, sizeof(float), 3, stl) < 3)
            badStl();
        
        if(fread(&byteCount, sizeof(uint16_t), 1, stl) < 1)
            badStl();
        
        printf("\tnormal %f %f %f\n", normal[0], normal[1], normal[2]);
        printf("\tv1 %f %f %f\n", v1[0], v1[1], v1[2]);
        printf("\tv2 %f %f %f\n", v2[0], v2[1], v2[2]);
        printf("\tv3 %f %f %f\n", v3[0], v3[1], v3[2]);
        
        if(output) {
            
            fprintf(output, " %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff, %ff", v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], v3[0], v3[1], v3[2]);
            
            if(i != nFacets - 1) {
                
                fprintf(output, ",");
            }
        }
    }
    
    if(output) {
        
        fprintf(output, " };\n\n");
        fprintf(output, "void glVertexFromMemory(int i) {\n\n    glVertex3f(pgm_read_float(&model[i*3 + 0]), pgm_read_float(&model[i*3 + 1]), pgm_read_float(&model[i*3 + 2]));\n}\n\n");
        
        fprintf(output, "void drawModel(void) {\n\n    int i;\n\n    for(i = 0; i < %u; i++) {\n\n        glBegin(GL_POLYGON);\n        glVertexFromMemory(i*3);\n        glVertexFromMemory(i*3 + 1);\n        glVertexFromMemory(i*3 + 2);\n        glEnd();\n    }\n}\n\n", nFacets);
        
        fclose(output);
    }
    
    fclose(stl);
    
    return 0;
}


