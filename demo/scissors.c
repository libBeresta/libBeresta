/*
 * `libBeresta`
 *
 * scissors.c - Минимально возможный пример
 * ==========
 *
 * Copyright (c) 2025 Dmitry Solomennikov
 *
 * Текст лиценции смотри в файле `ЛИЦЕНЗИЯ`
 */

/** en
  \par Complex path drawing example
*/

/** ru
  \par Пример отрисовки сложного объекта
*/

#include "brst.h"
#include "handler.h"
#include "cli.h"
#include <setjmp.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    BRST_Doc pdf;
    BRST_Page page;

    char* fname = prepare_output(argc, argv);
    if (fname == NULL) {
        print_error("file name too long");
        return 1;
    }

    // Создание объекта документа
    pdf = BRST_Doc_New(demo_error_handler, NULL);
    if (!pdf) {
        print_error("cannot create Doc object");
        return 1;
    }

    if (setjmp(env)) {
        BRST_Doc_Free(pdf);
        return 1;
    }

    // Добавление страницы
    page = BRST_Doc_Page_Add(pdf);

    // Настройка размера и ориентации страницы
    BRST_Page_SetSize(page, BRST_PAGE_SIZE_A4, BRST_PAGE_ORIENTATION_LANDSCAPE);

    BRST_Page_Scale(page, BRST_MM, BRST_MM);

    // Отрисовка ножниц
    BRST_Page_MoveTo(page,  30.465, 50.000);
    BRST_Page_CurveTo(page, 30.141, 50.000, 29.798, 49.990, 29.423, 49.968);
    BRST_Page_CurveTo(page, 28.366, 49.907, 27.900, 49.808, 26.917, 49.437);
    BRST_Page_CurveTo(page, 25.329, 48.839, 24.564, 48.222, 23.755, 46.889);
    BRST_Page_CurveTo(page, 23.406, 46.314, 23.037, 44.784, 23.090, 44.134);
    BRST_Page_CurveTo(page, 23.124, 43.730, 23.874, 41.793, 24.162, 41.368);
    BRST_Page_CurveTo(page, 24.264, 41.218, 24.663, 40.629, 25.050, 40.058);
    BRST_Page_CurveTo(page, 25.436, 39.488, 26.147, 38.496, 26.629, 37.855);
    BRST_Page_LineTo(page,  27.506, 36.689);
    BRST_Page_LineTo(page,  26.897, 35.455);
    BRST_Page_CurveTo(page, 26.562, 34.776, 26.229, 34.112, 26.157, 33.980);
    BRST_Page_CurveTo(page, 26.048, 33.781, 26.081, 33.693, 26.351, 33.464);
    BRST_Page_CurveTo(page, 27.099, 32.830, 27.112, 32.831, 28.127, 33.606);
    BRST_Page_CurveTo(page, 28.634, 33.994, 29.236, 34.398, 29.465, 34.504);
    BRST_Page_CurveTo(page, 29.967, 34.737, 30.232, 34.645, 32.447, 33.468);
    BRST_Page_CurveTo(page, 35.268, 31.969, 36.495, 31.004, 37.510, 29.486);
    BRST_Page_CurveTo(page, 38.319, 28.275, 38.599, 27.712, 39.674, 25.139);
    BRST_Page_CurveTo(page, 40.883, 22.245, 41.679, 19.225, 42.169, 15.672);
    BRST_Page_CurveTo(page, 42.283, 14.846, 42.487, 13.372, 42.624, 12.396);
    BRST_Page_CurveTo(page, 42.760, 11.420, 42.851, 10.574, 42.827, 10.518);
    BRST_Page_CurveTo(page, 42.802, 10.461, 42.571, 10.361, 42.313, 10.295);
    BRST_Page_CurveTo(page, 41.971, 10.208, 41.675, 10.228, 41.227, 10.370);
    BRST_Page_CurveTo(page, 40.473, 10.610, 40.386, 10.709, 38.731, 13.213);
    BRST_Page_CurveTo(page, 38.069, 14.215, 37.492, 15.049, 37.449, 15.067);
    BRST_Page_CurveTo(page, 37.350, 15.107, 36.315, 16.274, 36.281, 16.384);
    BRST_Page_CurveTo(page, 36.225, 16.563, 34.469, 18.088, 33.684, 18.638);
    BRST_Page_CurveTo(page, 32.931, 19.166, 32.420, 19.406, 28.552, 21.040);
    BRST_Page_CurveTo(page, 22.660, 23.531, 14.339, 26.641, 11.423, 27.442);
    BRST_Page_CurveTo(page,  9.652, 27.929,  8.743, 28.090,  6.762, 28.266);
    BRST_Page_CurveTo(page,  3.407, 28.564,  1.155, 27.368,  0.319, 24.844);
    BRST_Page_CurveTo(page,  0.032, 23.977,  0.000, 22.817,  0.060, 22.151);
    BRST_Page_CurveTo(page,  0.474, 20.174,  2.043, 17.789,  3.955, 16.230);
    BRST_Page_CurveTo(page,  4.974, 15.400,  6.782, 14.092,  7.551, 13.629);
    BRST_Page_CurveTo(page,  9.988, 12.162, 13.826, 10.284, 15.641,  9.671);
    BRST_Page_CurveTo(page, 19.317,  8.429, 20.834,  8.049, 24.083,  7.559);
    BRST_Page_CurveTo(page, 27.296,  7.074, 28.808,  7.036, 30.596,  7.396);
    BRST_Page_CurveTo(page, 31.634,  7.605, 33.379,  8.366, 34.047,  8.901);
    BRST_Page_CurveTo(page, 35.451, 10.027, 36.172,  9.764, 38.444,  7.298);
    BRST_Page_CurveTo(page, 39.335,  6.332, 39.778,  6.015, 40.333,  5.947);
    BRST_Page_CurveTo(page, 40.580,  5.917, 41.350,  5.820, 42.042,  5.731);
    BRST_Page_CurveTo(page, 42.735,  5.642, 43.753,  5.544, 44.305,  5.513);
    BRST_Page_CurveTo(page, 44.856,  5.482, 45.854,  5.399, 46.522,  5.328);
    BRST_Page_CurveTo(page, 47.189,  5.258, 48.209,  5.164, 48.788,  5.119);
    BRST_Page_LineTo(page,  49.840,  5.037);
    BRST_Page_LineTo(page,  54.098,  3.415);
    BRST_Page_CurveTo(page, 56.440,  2.523, 58.425,  1.788, 58.510, 1.782);
    BRST_Page_CurveTo(page, 58.594,  1.775, 58.655,  1.824, 58.645, 1.889);
    BRST_Page_CurveTo(page, 58.634,  1.954, 58.684,  2.017, 58.757, 2.028);
    BRST_Page_CurveTo(page, 58.829,  2.039, 58.870,  2.005, 58.847, 1.952);
    BRST_Page_CurveTo(page, 58.825,  1.900, 58.961,  1.708, 59.150, 1.526);
    BRST_Page_CurveTo(page, 59.419,  1.268, 60.017,  0.988, 62.418, 0.000);
    BRST_Page_LineTo(page,  78.349,  0.000);
    BRST_Page_CurveTo(page, 72.283,  2.989, 70.348,  3.970, 70.333,  4.065);
    BRST_Page_CurveTo(page, 70.326,  4.106, 71.382,  4.125, 72.680,  4.104);
    BRST_Page_CurveTo(page, 73.977,  4.084, 75.746,  4.069, 76.611,  4.071);
    BRST_Page_CurveTo(page, 79.819,  4.077, 81.022,  4.064, 83.647,  3.995);
    BRST_Page_CurveTo(page, 86.675,  3.917, 90.214,  4.004, 96.286,  4.308);
    BRST_Page_CurveTo(page, 97.169,  4.352, 98.348,  4.407, 98.906,  4.429);
    BRST_Page_CurveTo(page, 99.823,  4.466, 99.999,  4.587, 99.878,  4.725);
    BRST_Page_CurveTo(page, 99.104,  5.036, 93.279,  6.937, 92.857,  7.017);
    BRST_Page_CurveTo(page, 92.549,  7.075, 91.532,  7.301, 90.596,  7.520);
    BRST_Page_CurveTo(page, 87.659,  8.206, 80.733,  9.350, 76.660,  9.820);
    BRST_Page_CurveTo(page, 76.344,  9.857, 75.026, 10.017, 73.732, 10.176);
    BRST_Page_CurveTo(page, 72.438, 10.335, 69.153, 10.727, 66.433, 11.047);
    BRST_Page_LineTo(page,  61.488, 11.630);
    BRST_Page_LineTo(page,  61.091, 11.333);
    BRST_Page_CurveTo(page, 60.782, 11.102, 60.713, 11.084, 60.783, 11.250);
    BRST_Page_CurveTo(page, 60.903, 11.534, 60.734, 11.828, 60.420, 11.885);
    BRST_Page_CurveTo(page, 60.281, 11.910, 58.832, 12.051, 57.200, 12.198);
    BRST_Page_CurveTo(page, 51.250, 12.734, 52.011, 12.602, 50.286, 13.400);
    BRST_Page_CurveTo(page, 48.683, 14.142, 47.803, 14.679, 47.412, 15.152);
    BRST_Page_CurveTo(page, 46.851, 15.834, 46.324, 17.347, 45.844, 19.657);
    BRST_Page_CurveTo(page, 45.574, 20.957, 45.385, 21.773, 45.176, 22.543);
    BRST_Page_CurveTo(page, 44.953, 23.362, 44.388, 24.874, 43.413, 27.265);
    BRST_Page_CurveTo(page, 42.209, 30.215, 41.989, 30.816, 41.949, 31.271);
    BRST_Page_CurveTo(page, 41.886, 31.979, 42.040, 32.960, 42.412, 34.223);
    BRST_Page_CurveTo(page, 43.087, 36.511, 43.136, 37.293, 42.737, 39.421);
    BRST_Page_CurveTo(page, 42.177, 42.406, 39.816, 45.825, 36.815, 47.998);
    BRST_Page_CurveTo(page, 36.355, 48.330, 35.779, 48.610, 34.546, 49.099);
    BRST_Page_CurveTo(page, 32.916, 49.746, 31.871, 49.993, 30.465, 50.000);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page,  30.858, 47.955);
    BRST_Page_CurveTo(page, 31.179, 47.952, 31.493, 47.929, 31.791, 47.883);
    BRST_Page_CurveTo(page, 32.860, 47.719, 35.324, 46.544, 36.403, 45.682);
    BRST_Page_CurveTo(page, 38.238, 44.218, 39.768, 42.111, 40.526, 40.003);
    BRST_Page_CurveTo(page, 41.000, 38.685, 41.099, 37.930, 40.955, 36.730);
    BRST_Page_CurveTo(page, 40.756, 35.070, 40.195, 34.126, 39.149, 33.690);
    BRST_Page_CurveTo(page, 37.875, 33.160, 37.280, 33.303, 34.956, 34.703);
    BRST_Page_CurveTo(page, 32.643, 36.095, 27.981, 39.778, 27.420, 40.656);
    BRST_Page_CurveTo(page, 27.381, 40.718, 27.107, 40.995, 26.813, 41.272);
    BRST_Page_CurveTo(page, 25.901, 42.129, 25.509, 42.820, 25.437, 43.701);
    BRST_Page_CurveTo(page, 25.388, 44.301, 25.427, 44.600, 25.611, 45.029);
    BRST_Page_CurveTo(page, 25.914, 45.734, 26.574, 46.584, 27.144, 47.002);
    BRST_Page_CurveTo(page, 27.957, 47.598, 29.469, 47.968, 30.858, 47.955);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page,   5.880, 25.801);
    BRST_Page_CurveTo(page,  6.427, 25.821,  6.559, 25.772, 12.917, 23.181);
    BRST_Page_CurveTo(page, 18.838, 20.767, 19.725, 20.432, 23.209, 19.288);
    BRST_Page_CurveTo(page, 25.306, 18.600, 27.793, 17.806, 28.735, 17.524);
    BRST_Page_CurveTo(page, 29.677, 17.241, 30.884, 16.809, 31.416, 16.564);
    BRST_Page_CurveTo(page, 32.299, 16.156, 32.445, 16.049, 33.080, 15.345);
    BRST_Page_CurveTo(page, 34.067, 14.253, 34.254, 13.347, 33.740, 12.148);
    BRST_Page_CurveTo(page, 33.329, 11.191, 32.730, 10.697, 31.298, 10.130);
    BRST_Page_CurveTo(page, 30.601,  9.855, 29.919,  9.639, 29.783,  9.651);
    BRST_Page_CurveTo(page, 29.647,  9.663, 29.521,  9.636, 29.501,  9.591);
    BRST_Page_CurveTo(page, 29.423,  9.409, 26.971,  9.560, 25.087,  9.863);
    BRST_Page_CurveTo(page, 23.027, 10.194, 20.590, 10.718, 18.671, 11.243);
    BRST_Page_CurveTo(page, 17.337, 11.608, 13.164, 13.352, 11.295, 14.327);
    BRST_Page_CurveTo(page,  9.734, 15.141,  6.859, 16.938,  6.244, 17.483);
    BRST_Page_CurveTo(page,  4.334, 19.177,  3.204, 20.970,  3.118, 22.443);
    BRST_Page_CurveTo(page,  3.008, 24.350,  4.150, 25.740,  5.880, 25.801);
    BRST_Page_ClosePath(page);

    BRST_Page_MoveTo(page, 50.480, 10.650);
    BRST_Page_CurveTo(page,  50.707, 10.650, 50.938, 10.604, 51.167, 10.510);
    BRST_Page_CurveTo(page,  52.087, 10.133, 52.434,  9.330, 52.112,  8.325);
    BRST_Page_CurveTo(page,  51.904,  7.678, 51.493,  7.332, 50.812,  7.231);
    BRST_Page_CurveTo(page,  50.275,  7.151, 50.042,  7.234, 50.392,  7.380);
    BRST_Page_CurveTo(page,  50.534,  7.440, 50.661,  7.436, 50.674,  7.373);
    BRST_Page_CurveTo(page,  50.710,  7.205, 51.327,  7.571, 51.618,  7.932);
    BRST_Page_CurveTo(page,  51.943,  8.337, 52.028,  8.697, 51.952,  9.156);
    BRST_Page_CurveTo(page,  51.927,  9.686, 51.265,  9.975, 50.916, 10.129);
    BRST_Page_CurveTo(page,  50.489, 10.313, 50.307, 10.332, 49.963, 10.227);
    BRST_Page_CurveTo(page,  49.365, 10.045, 49.004,  9.589, 48.963,  8.963);
    BRST_Page_CurveTo(page,  48.927,  8.431, 48.767,  8.338, 48.784,  8.859);
    BRST_Page_CurveTo(page,  48.804,  9.504, 48.863,  9.695, 49.141, 10.014);
    BRST_Page_CurveTo(page,  49.507, 10.432, 49.982, 10.651, 50.480, 10.650);
    BRST_Page_ClosePath(page);
    BRST_Page_Fill(page);

    // Сохранение документа в файл
    BRST_Doc_SaveToFile(pdf, fname);

    // Очистка
    BRST_Doc_Free(pdf);

    return 0;
}
