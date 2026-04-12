#include <stdio.h>
#include <math.h>

int main() {
    FILE *arquivo = fopen("cordic_lut.h", "w");
    
    if (arquivo == NULL) {
        printf("Erro fatal: Nao foi possivel criar o arquivo cordic_lut.h\n");
        return 1; 
    }

    // Escreve o include guard
    fprintf(arquivo, "#ifndef CORDIC_LUT_H\n");
    fprintf(arquivo, "#define CORDIC_LUT_H\n\n");

    fprintf(arquivo, "// Tabela LUT de arctan(2^-i) precalculada em RADIANOS\n");
    fprintf(arquivo, "const float CORDIC_LUT[24] = {\n");

    for (int i = 0; i < 24; i++) {
        double value = atan(pow(2.0, -i));

        if (i < 23) {
            fprintf(arquivo, "    %.9ff,\n", value);
        } else {
            fprintf(arquivo, "    %.9ff\n", value);
        }
    }
    
    // Fecha o array e o include guard
    fprintf(arquivo, "};\n\n");
    fprintf(arquivo, "#endif // CORDIC_LUT_H\n");

    // Salva e libera a memória
    fclose(arquivo);

    printf("Sucesso! Arquivo 'cordic_lut.h' gerado com os 24 angulos.\n");

    return 0;
}
