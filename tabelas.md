
================================================================================
TABELA 1: LATÊNCIA E DESEMPENHO COMPUTACIONAL (MARKDOWN)
================================================================================
| Operação         |   Tempo Total (s) |   Latência (ns/op) |   Ciclos Médios | Slowdown    |
|:-----------------|------------------:|-------------------:|----------------:|:------------|
| CORDIC_sin_cos   |            0.1719 |             171.88 |           446.2 | 22.09x      |
| math_sin_cos     |            0.0078 |               7.78 |            20.2 | 1.00x (ref) |
| CORDIC_sinh_cosh |            0.2236 |             223.59 |           580.5 | 53.06x      |
| math_sinh_cosh   |            0.0042 |               4.21 |            10.9 | 1.00x (ref) |
| CORDIC_sqrt      |            0.1871 |             187.1  |           485.7 | 44.21x      |
| math_sqrt        |            0.0042 |               4.23 |            11   | 1.00x (ref) |
-> Imagem salva: tabela_benchmark.png
-> Código LaTeX salvo: tabela_benchmark.tex

================================================================================
TABELA 2: EVOLUÇÃO DO ERRO POR ITERAÇÃO (MARKDOWN)
================================================================================
|   N |   Limite Teórico (2^-N) |   Erro Sin(pi/4) |   Erro Cos(pi/4) |   Erro Sinh(0.5) |   Erro Exp(1.0) |   Erro Sqrt(2.0) |
|----:|------------------------:|-----------------:|-----------------:|-----------------:|----------------:|-----------------:|
|   4 |                0.0625   |         0.0614   |         0.0714   |         0.0513   |           0.801 |         0.00285  |
|   8 |                0.00391  |         0.00509  |         0.00503  |         0.00196  |           0.912 |         4.98e-06 |
|  12 |                0.000244 |         0.000119 |         0.000119 |         2.78e-05 |           0.906 |         4.57e-08 |
|  16 |                1.53e-05 |         1.1e-05  |         1.1e-05  |         1.06e-05 |           0.906 |         7.11e-11 |
|  20 |                9.54e-07 |         1.16e-06 |         1.16e-06 |         9.02e-07 |           0.906 |         2.13e-13 |
|  24 |                5.96e-08 |         6.22e-08 |         6.22e-08 |         2.83e-08 |           0.906 |         2.22e-16 |
-> Imagem salva: tabela_convergencia.png
-> Código LaTeX salvo: tabela_convergencia.tex

================================================================================
TABELA 3: RESUMO ESTATÍSTICO DO ERRO NO 1º QUADRANTE (MARKDOWN)
================================================================================
| Métrica              |     Seno |   Cosseno |   Tangente |
|:---------------------|---------:|----------:|-----------:|
| Erro Absoluto Médio  | 3.78e-08 |  3.79e-08 |   0.000409 |
| Erro Absoluto Máximo | 1.17e-07 |  1.18e-07 |   0.126    |
| Desvio Padrão        | 3.04e-08 |  3.05e-08 |   0.0071   |
-> Imagem salva: tabela_estatistica_quadrante.png
-> Código LaTeX salvo: tabela_estatistica.tex
