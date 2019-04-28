/*-------------------------------------------------------------------
   ADDSYNTH.H -- Amplitude and Frequency Envelopes for 3 Instruments

				 From "Computer Music Journal," Volume II, Number 2
  -------------------------------------------------------------------*/

#include <stdlib.h>

typedef struct
{
	int iTime;
	int iValue;
}
ENV;

typedef struct
{
	int  iNumAmp;
	ENV* pEnvAmp;
	int  iNumFrq;
	ENV* pEnvFrq;
}
PRT;

typedef struct
{
	int   iMsecTime;
	int   iNumPartials;
	PRT* pprt;
}
INS;

ENV envTrumAmp01[] = { 1,    0,  20,  305,  36,  338, 141,  288, 237,   80,
					   360,    0 };

ENV envTrumFrq01[] = { 1,  321,  16,  324,  32,  312, 109,  310, 317,  314,
					   360,  310 };

ENV envTrumAmp02[] = { 1,    0,   3,    0,  25,  317,  39,  361, 123,  295,
					   222,   40, 326,    0, 360,    0 };

ENV envTrumFrq02[] = { 1,    0,   2,    0,   3,  607,  16,  657,  24,  621,
					   133,  621, 275,  628, 326,  628, 327,    0, 360,    0 };

ENV envTrumAmp03[] = { 1,    0,   2,    0,  19,  100,  34,  369, 111,  342,
					   207,   41, 273,    0, 360,    0 };

ENV envTrumFrq03[] = { 1,    0,   2,  977,   5,  782,  15,  987,  24,  932,
					   128,  932, 217,  936, 273,  945, 275,    0, 360,    0 };

ENV envTrumAmp04[] = { 1,    0,   3,    0,  24,  113,  29,  257, 118,  231,
					   187,   35, 235,    0, 360,    0 };

ENV envTrumFrq04[] = { 1,    0,   2,    0,   3,  718,  16, 1335,  24, 1243,
					   108, 1240, 199, 1248, 235, 1248, 236,    0, 360,    0 };

ENV envTrumAmp05[] = { 1,    0,  27,   52,  34,  130, 110,  126, 191,   13,
					   234,    0, 360,    0 };

ENV envTrumFrq05[] = { 1, 1225,   9, 1569,  12, 1269,  21, 1573,  37, 1553,
						97, 1552, 181, 1556, 234, 1566, 235,    0, 360,    0 };

ENV envTrumAmp06[] = { 1,    0,  46,   83,  64,  100, 100,  100, 189,   11,
					   221,    0, 360,    0 };

ENV envTrumFrq06[] = { 1, 1483,  12, 1572,  23, 1988,  33, 1864, 114, 1864,
					   177, 1868, 221, 1879, 222,    0, 360,    0 };

ENV envTrumAmp07[] = { 1,    0,  37,   39,  45,   77, 110,   79, 176,   11,
					   205,    0, 207,    0, 360,    0 };

ENV envTrumFrq07[] = { 1, 1792,   9, 1612,  29, 2242,  36, 2174,  93, 2176,
					   126, 2170, 205, 2188, 207,    0, 360,    0 };

ENV envTrumAmp08[] = { 1,    0,   2,    0,  28,   17,  43,   71, 109,   66,
					   172,    8, 201,    0, 360,    0 };

ENV envTrumFrq08[] = { 1,    0,   2, 1590,  29, 2539,  36, 2491, 114, 2481,
					   153, 2489, 201, 2491, 203,    0, 360,    0 };

ENV envTrumAmp09[] = { 1,    0,   2,    0,  29,   16,  43,   53,  54,   66,
					   105,   64, 165,    7, 191,    0, 360,    0 };

ENV envTrumFrq09[] = { 1,    0,   2, 1993,  25, 2121,  32, 2821,  37, 2796,
						84, 2798, 105, 2792, 191, 2797, 192,    0, 360,    0 };

ENV envTrumAmp10[] = { 1,    0,  27,    6,  41,   25,  56,   29,  72,   22,
						95,   24, 180,    0, 360,    0 };

ENV envTrumFrq10[] = { 1, 1792,  12, 1849,  32, 3131,  37, 3111, 114, 3103,
					   164, 3116, 180, 3116, 181,    0, 360,    0 };

ENV envTrumAmp11[] = { 1,    0,   2,    0,  37,    6,  55,   25,  88,   29,
					   114,   28, 164,    3, 186,    0, 360,    0 };

ENV envTrumFrq11[] = { 1,    0,   2, 1398,  31, 3419,  42, 3419,  91, 3419,
					   106, 3406, 150, 3421, 186, 3421, 187,    0, 360,    0 };

ENV envTrumAmp12[] = { 1,    0,   7,    0,  39,    3,  43,    8,  88,   11,
					   118,    9, 138,    3, 165,    0, 360,    0 };

ENV envTrumFrq12[] = { 1,    0,   6,    0,   7, 1806,  23, 2942,  36, 2759,
						37, 3746,  50, 3723,  84, 3731, 110, 3721, 156, 3741,
					   165, 3620, 167,    0, 360,    0 };

ENV envOboeAmp01[] = { 1,    0,   9,    0,  14,   10,  26,   10,  52,  140,
						94,  187, 153,  170, 313,    0 };

ENV envOboeFrq01[] = { 1,    0,   8,    0,   9,  314,  25,  292,  43,  311,
					   144,  311, 272,  313, 313,  309 };

ENV envOboeAmp02[] = { 1,    0,  10,    0,  26,   17,  40,  139, 159,  115,
					   239,   62, 307,    0, 313,    0 };

ENV envOboeFrq02[] = { 1,    0,   9,    0,  10,  708,  16,  617,  41,  625,
					   105,  621, 265,  630, 307,  626, 308,    0, 313,    0 };

ENV envOboeAmp03[] = { 1,    0,  10,    0,  25,   19,  36,  163,  71,  191,
					   129,  187, 297,    0, 313,    0 };

ENV envOboeFrq03[] = { 1,    0,   9,    0,  10,  915,  21,  931,  72,  938,
					   148,  935, 249,  941, 297,  938, 299,    0, 313,    0 };

ENV envOboeAmp04[] = { 1,    0,  10,    0,  25,   16,  43,  221,  64,  173,
					   114,  171, 284,    0, 313,    0 };

ENV envOboeFrq04[] = { 1,    0,   9,    0,  10, 1209,  18, 1261,  37, 1246,
					   109, 1245, 238, 1255, 284, 1253, 285,    0, 313,    0 };

ENV envOboeAmp05[] = { 1,    0,   6,    0,  13,    3,  21,    0,  28,    0,
						44,  210,  59,  238, 126,  224, 199,   85, 292,    0,
						313,    0 };

ENV envOboeFrq05[] = { 1,    0,   5,    0,   6, 1553,  21, 1582,  25, 1237,
						28, 1533,  35, 1564,  56, 1557, 113, 1555, 185, 1565,
					   292, 1566, 293,    0, 313,    0 };

ENV envOboeAmp06[] = { 1,    0,  13,    0,  17,    1,  24,    0,  30,    0,
						41,   63,  67,   40, 121,   38, 278,    0, 313,    0 };

ENV envOboeFrq06[] = { 1,    0,  12,    0,  13, 1907,  22, 1883,  28, 1544,
						30, 1856,  36, 1878,  52, 1871, 113, 1866, 169, 1878,
					   225, 1876, 278, 1891, 280,    0, 313,    0 };

ENV envOboeAmp07[] = { 1,    0,   8,    0,  14,    0,  21,    0,  32,    0,
						37,   22, 119,   12, 146,    3, 194,    8, 256,    0,
					   313,    0 };

ENV envOboeFrq07[] = { 1,    0,   6,    0,   8, 1978,  21, 1923,  28, 1717,
						32, 2191, 111, 2177, 188, 2193, 229, 2182, 256, 2194,
					   257,    0, 313,    0 };

ENV envOboeAmp08[] = { 1,    0,   6,    0,  14,    0,  21,    0,  37,    0,
						66,    5, 106,    3, 129,    4, 199,    3, 235,    0,
					   313,    0 };

ENV envOboeFrq08[] = { 1,    0,   5,    0,   6, 2506,  21, 2491,  25, 1252,
						37, 2523,  56, 2495, 110, 2489, 140, 2491, 195, 2502,
					   235, 2505, 237,    0, 313,    0 };

ENV envOboeAmp09[] = { 1,    0,   4,    0,  14,    0,  20,    0,  36,    0,
						45,   32,  78,   24, 132,   25, 161,   15, 241,    0,
					   313,    0 };

ENV envOboeFrq09[] = { 1,    0,   2,    0,   4, 2783,  20, 2779,  29, 1286,
						37, 2803,  80, 2806, 113, 2799, 167, 2813, 241, 2818,
					   242,    0, 313,    0 };

ENV envOboeAmp10[] = { 1,    0,   6,    0,  17,    2,  22,    0,  35,    0,
						47,  121, 144,  112, 206,   21, 242,    0, 313,    0 };

ENV envOboeFrq10[] = { 1,    0,   5,    0,   6, 3123,  22, 3115,  29, 2229,
						35, 3118,  70, 3117, 113, 3109, 200, 3130, 242, 3131,
					   243,    0, 313,    0 };

ENV envOboeAmp11[] = { 1,    0,   5,    0,  17,    1,  24,    0,  37,    0,
						47,   70, 123,   67, 167,   44, 188,   16, 239,    0,
					   313,    0 };

ENV envOboeFrq11[] = { 1,    0,   4,    0,   5, 3285,  24, 3388,  29, 1270,
						37, 3430,  76, 3429, 110, 3423, 194, 3444, 239, 3444,
					   241,    0, 313,    0 };

ENV envOboeAmp12[] = { 1,    0,  14,    1,  24,    0,  37,    0,  44,   49,
						79,   42, 122,   46, 185,    8, 231,    0, 313,    0 };

ENV envOboeFrq12[] = { 1, 3627,  24, 3664,  29, 1690,  37, 3739,  90, 3742,
					   115, 3733, 187, 3760, 231, 3763, 233,    0, 313,    0 };

ENV envOboeAmp13[] = { 1,    0,   4,    0,  16,    0,  24,    0,  40,    0,
						47,   27,  84,   22, 126,   24, 177,    7, 229,    0,
					   313,    0 };

ENV envOboeFrq13[] = { 1,    0,   2,    0,   4, 4081,  24, 4064,  30, 1350,
						40, 4064,  57, 4049, 148, 4051, 181, 4074, 229, 4069,
					   230,    0, 313,    0 };

ENV envOboeAmp14[] = { 1,    0,   4,    0,  16,    0,  21,    0,  41,    0,
						44,   13,  63,    8,  82,    7, 111,   10, 175,    0,
					   313,    0 };

ENV envOboeFrq14[] = { 1,    0,   2,    0,   4, 4321,  21, 4259,  29, 1238,
						41, 4346,  61, 4367,  87, 4368, 102, 4357, 175, 4376,
					   176,    0, 313,    0 };

ENV envOboeAmp15[] = { 1,    0,  47,    0,  72,    3,  97,    3, 121,    1,
					   161,    2, 175,    0, 313,    0 };

ENV envOboeFrq15[] = { 1,    0,  45,    0,  47, 3164,  55, 4557,  68, 4662,
						98, 4670, 142, 4661, 175, 4666, 176,    0, 313,    0 };

ENV envOboeAmp16[] = { 1,    0,  48,    0,  61,    4,  86,    4, 126,    3,
					   137,    5, 161,    0, 313,    0 };

ENV envOboeFrq16[] = { 1,    0,  47,    0,  48, 4567,  49, 4978,  75, 4990,
					   109, 4982, 138, 4985, 161, 4996, 163,    0, 313,    0 };

ENV envOboeAmp17[] = { 1,    0,  51,    0,  61,    5,  76,    3, 132,    3,
					   164,    2, 173,    0, 313,    0 };

ENV envOboeFrq17[] = { 1,    0,  49,    0,  51, 4634,  55, 5313,  66, 5301,
						99, 5301, 129, 5292, 173, 5318, 175,    0, 313,    0 };

ENV envOboeAmp18[] = { 1,    0,  52,    0,  63,    2,  91,    3, 126,    3,
					   156,    2, 168,    0, 313,    0 };

ENV envOboeFrq18[] = { 1,    0,  51,    0,  52, 4729,  59, 5606,  92, 5611,
					   122, 5605, 152, 5611, 168, 5628, 169,    0, 313,    0 };

ENV envOboeAmp19[] = { 1,    0,  47,    0,  56,    2,  80,    1, 117,    2,
					   159,    1, 176,    0, 313,    0 };

ENV envOboeFrq19[] = { 1,    0,  45,    0,  47, 5772,  57, 5921,  86, 5928,
					   114, 5914, 150, 5938, 176, 5930, 177,    0, 313,    0 };

ENV envOboeAmp20[] = { 1,    0,  49,    0,  57,    2,  83,    2, 109,    1,
					   159,    3, 195,    0, 313,    0 };

ENV envOboeFrq20[] = { 1,    0,  48,    0,  49, 5369,  57, 6268,  76, 6230,
					   145, 6234, 184, 6263, 195, 6244, 196,    0, 313,    0 };

ENV envOboeAmp21[] = { 1,    0,  57,    0,  61,    0,  88,    1, 113,    0,
					   129,    1, 140,    0, 313,    0 };

ENV envOboeFrq21[] = { 1,    0,  56,    0,  57, 5477,  61, 6440,  71, 6550,
						97, 6538, 122, 6554, 140, 6548, 141,    0, 313,    0 };

ENV envClarAmp01[] = { 1,    0,   7,    0,  20,    6,  32,   73,  48,  445,
					   199,  361, 330,    0 };

ENV envClarFrq01[] = { 1,    0,   6,    0,   7,  282,  19,  368,  21,  314,
						46,  310, 141,  312, 284,  313, 330,  314 };

ENV envClarAmp02[] = { 1,    0,  24,    0,  43,   22, 104,    2, 193,    4,
					   238,   10, 301,    0, 330,    0 };

ENV envClarFrq02[] = { 1,    0,  23,    0,  24,  629,  68,  619, 116,  616,
					   167,  633, 223,  624, 301,  627, 302,    0, 330,    0 };

ENV envClarAmp03[] = { 1,    0,  15,    0,  37,   12,  48,  159, 204,  122,
					   286,   17, 309,    0, 330,    0 };

ENV envClarFrq03[] = { 1,    0,  14,    0,  15,  803,  24,  928,  36,  898,
						46,  931, 113,  939, 330,  942 };

ENV envClarAmp04[] = { 1,    0,   9,    0,  19,    2,  24,    0,  39,    0,
						49,   26, 103,    3, 167,    5, 229,   10, 291,    0,
					   330,    0 };

ENV envClarFrq04[] = { 1,    0,   7,    0,   9, 1261,  24, 1314,  30,  327,
						39, 1245, 105, 1243, 215, 1257, 246, 1249, 291, 1261,
					   292,    0, 330,    0 };

ENV envClarAmp05[] = { 1,    0,   6,    0,  18,    5,  25,    0,  39,    0,
						54,  375, 212,  210, 266,   20, 295,    0, 330,    0 };

ENV envClarFrq05[] = { 1,    0,   5,    0,   6, 1572,  25, 1528,  32,  911,
						38, 1560,  67, 1554, 127, 1565, 308, 1569, 309,    0,
					   330,    0 };

ENV envClarAmp06[] = { 1,    0,   3,    0,  11,    0,  15,    0,  41,    0,
						48,   25, 108,    4, 216,   12, 282,    0, 330,    0 };

ENV envClarFrq06[] = { 1,    0,   2,    0,   3, 1934,  12, 1890,  33,  320,
						46, 1862, 186, 1883, 282, 1875, 283,    0, 330,    0 };

ENV envClarAmp07[] = { 1,    0,   2,    0,  18,    1,  24,    0,  42,    0,
						52,  108, 127,   46, 177,   42, 253,    0, 330,    0 };

ENV envClarFrq07[] = { 1,    0,   2, 2180,  24, 2148,  34,  795,  43, 2167,
					   113, 2193, 253, 2192, 255,    0, 330,    0 };

ENV envClarAmp08[] = { 1,    0,   2,    0,  14,    1,  23,    0,  43,    0,
						52,   83, 110,   17, 199,   18, 242,    0, 330,    0 };

ENV envClarFrq08[] = { 1,    0,   2, 2458,  23, 2343,  33,  328,  45, 2472,
					   125, 2507, 242, 2510, 243,    0, 330,    0 };

ENV envClarAmp09[] = { 1,    0,   5,    0,  20,    2,  21,    3,  27,    0,
						42,    0,  55,  127, 132,   73, 163,   71, 255,    0,
					   330,    0 };

ENV envClarFrq09[] = { 1,    0,   3,    0,   5, 2849,  27, 2688,  33,  964,
						42, 2792, 128, 2822, 255, 2819, 256,    0, 330,    0 };

ENV envClarAmp10[] = { 1,    0,   5,    0,  23,    1,  30,    0,  47,    0,
						54,   32,  92,   17, 232,    7, 247,    0, 330,    0 };

ENV envClarFrq10[] = { 1,    0,   3,    0,   5, 3173,  30, 3030,  39, 2320,
						50, 3096, 134, 3136, 247, 3138, 248,    0, 330,    0 };

ENV envClarAmp11[] = { 1,    0,  23,    1,  28,    0,  39,    0,  59,   44,
					   122,   26, 153,   26, 262,    0, 330,    0 };

ENV envClarFrq11[] = { 1, 3313,  28, 3279,  34, 1768,  43, 3420, 127, 3448,
					   262, 3441, 264,    0, 330,    0 };

ENV envClarAmp12[] = { 1,    0,  10,    2,  21,    0,  46,    0,  52,   53,
					   158,    9, 206,   28, 255,    0, 330,    0 };

ENV envClarFrq12[] = { 1, 3756,  21, 3728,  33, 2095,  47, 3741, 136, 3762,
					   255, 3759, 256,    0, 330,    0 };

ENV envClarAmp13[] = { 1,    0,   3,    0,  16,    1,  29,    0,  41,    0,
						46,   24,  52,    8,  77,   57, 192,    8, 250,    0,
					   330,    0 };

ENV envClarFrq13[] = { 1,    0,   2,    0,   3, 4152,  29, 3868,  36, 2240,
						46, 4045,  85, 4049, 128, 4078, 181, 4078, 250, 4103,
					   251,    0, 330,    0 };

ENV envClarAmp14[] = { 1,    0,   3,    0,  16,    0,  20,    0,  48,    0,
						56,   38, 110,    3, 188,   14, 228,    0, 330,    0 };

ENV envClarFrq14[] = { 1,    0,   2,    0,   3, 4213,  20, 4119,  36, 1566,
						48, 4344, 130, 4388, 228, 4388, 229,    0, 330,    0 };

ENV envClarAmp15[] = { 1,    0,   5,    0,  23,    1,  28,    0,  50,    0,
						77,   14, 202,    1, 219,    2, 247,    0, 330,    0 };

ENV envClarFrq15[] = { 1,    0,   3,    0,   5, 4624,  28, 4496,  33, 1012,
						48, 4649, 122, 4703, 247, 4685, 248,    0, 330,    0 };

ENV envClarAmp16[] = { 1,    0,  14,    0,  24,    0,  38,    0,  64,   12,
					   104,    4, 145,    4, 215,    1, 238,    0, 330,    0 };

ENV envClarFrq16[] = { 1, 4928,  24, 4751,  36, 1072,  52, 4965, 117, 5006,
					   155, 5003, 198, 5020, 238, 3197, 239,    0, 330,    0 };

ENV envClarAmp17[] = { 1,    0,  58,    0,  95,   12, 136,   13, 201,    1,
					   220,    3, 233,    0, 330,    0 };

ENV envClarFrq17[] = { 1,    0,  45,    0,  46, 5005,  58, 3759,  63, 5285,
					   119, 5325, 180, 5325, 233, 5367, 234,    0, 330,    0 };

ENV envClarAmp18[] = { 1,    0,  50,    0,  61,    5, 100,    0, 141,    4,
					   185,    2, 208,    0, 330,    0 };

ENV envClarFrq18[] = { 1,    0,  48,    0,  50, 4926,  52, 5563,  94, 5628,
					   113, 5602, 137, 5634, 208, 5646, 210,    0, 330,    0 };

ENV envClarAmp19[] = { 1,    0,  58,    0,  63,    1,  85,    0, 140,    1,
					   171,    0, 183,    0, 330,    0 };

ENV envClarFrq19[] = { 1,    0,  56,    0,  58, 3938,  65, 5753,  79, 5930,
					   104, 5889, 152, 5916, 183, 5880, 184,    0, 330,    0 };

ENV envClarAmp20[] = { 1,    0,  50,    0,  64,    5, 103,    1, 139,    1,
					   177,    2, 219,    0, 330,    0 };

ENV envClarFrq20[] = { 1,    0,  48,    0,  50, 5192,  58, 6209, 121, 6266,
					   190, 6266, 204, 6238, 219, 6288, 220,    0, 330,    0 };

ENV envClarAmp21[] = { 1,    0,  70,    0,  79,    3, 113,    3, 141,    1,
					   206, 1, 219, 0,  330,   0 };

ENV envClarFrq21[] = { 1,    0,  69,    0,  70, 4245,  77, 6537, 116, 6567,
					   140, 6571, 176, 6564, 219, 6583, 220,    0, 330,    0 };

PRT prtTrum[12] = { _countof(envTrumAmp01) , envTrumAmp01,
					  _countof(envTrumFrq01) , envTrumFrq01,
					  _countof(envTrumAmp02) , envTrumAmp02,
					  _countof(envTrumFrq02) , envTrumFrq02,
					  _countof(envTrumAmp03) , envTrumAmp03,
					  _countof(envTrumFrq03) , envTrumFrq03,
					  _countof(envTrumAmp04) , envTrumAmp04,
					  _countof(envTrumFrq04) , envTrumFrq04,
					  _countof(envTrumAmp05) , envTrumAmp05,
					  _countof(envTrumFrq05) , envTrumFrq05,
					  _countof(envTrumAmp06) , envTrumAmp06,
					  _countof(envTrumFrq06) , envTrumFrq06,
					  _countof(envTrumAmp07) , envTrumAmp07,
					  _countof(envTrumFrq07) , envTrumFrq07,
					  _countof(envTrumAmp08) , envTrumAmp08,
					  _countof(envTrumFrq08) , envTrumFrq08,
					  _countof(envTrumAmp09) , envTrumAmp09,
					  _countof(envTrumFrq09) , envTrumFrq09,
					  _countof(envTrumAmp10) , envTrumAmp10,
					  _countof(envTrumFrq10) , envTrumFrq10,
					  _countof(envTrumAmp11) , envTrumAmp11,
					  _countof(envTrumFrq11) , envTrumFrq11,
					  _countof(envTrumAmp12) , envTrumAmp12,
					  _countof(envTrumFrq12) , envTrumFrq12 };

PRT prtOboe[21] = { _countof(envOboeAmp01) , envOboeAmp01,
					  _countof(envOboeFrq01) , envOboeFrq01,
					  _countof(envOboeAmp02) , envOboeAmp02,
					  _countof(envOboeFrq02) , envOboeFrq02,
					  _countof(envOboeAmp03) , envOboeAmp03,
					  _countof(envOboeFrq03) , envOboeFrq03,
					  _countof(envOboeAmp04) , envOboeAmp04,
					  _countof(envOboeFrq04) , envOboeFrq04,
					  _countof(envOboeAmp05) , envOboeAmp05,
					  _countof(envOboeFrq05) , envOboeFrq05,
					  _countof(envOboeAmp06) , envOboeAmp06,
					  _countof(envOboeFrq06) , envOboeFrq06,
					  _countof(envOboeAmp07) , envOboeAmp07,
					  _countof(envOboeFrq07) , envOboeFrq07,
					  _countof(envOboeAmp08) , envOboeAmp08,
					  _countof(envOboeFrq08) , envOboeFrq08,
					  _countof(envOboeAmp09) , envOboeAmp09,
					  _countof(envOboeFrq09) , envOboeFrq09,
					  _countof(envOboeAmp10) , envOboeAmp10,
					  _countof(envOboeFrq10) , envOboeFrq10,
					  _countof(envOboeAmp11) , envOboeAmp11,
					  _countof(envOboeFrq11) , envOboeFrq11,
					  _countof(envOboeAmp12) , envOboeAmp12,
					  _countof(envOboeFrq12) , envOboeFrq12,
					  _countof(envOboeAmp13) , envOboeAmp13,
					  _countof(envOboeFrq13) , envOboeFrq13,
					  _countof(envOboeAmp14) , envOboeAmp14,
					  _countof(envOboeFrq14) , envOboeFrq14,
					  _countof(envOboeAmp15) , envOboeAmp15,
					  _countof(envOboeFrq15) , envOboeFrq15,
					  _countof(envOboeAmp16) , envOboeAmp16,
					  _countof(envOboeFrq16) , envOboeFrq16,
					  _countof(envOboeAmp17) , envOboeAmp17,
					  _countof(envOboeFrq17) , envOboeFrq17,
					  _countof(envOboeAmp18) , envOboeAmp18,
					  _countof(envOboeFrq18) , envOboeFrq18,
					  _countof(envOboeAmp19) , envOboeAmp19,
					  _countof(envOboeFrq19) , envOboeFrq19,
					  _countof(envOboeAmp20) , envOboeAmp20,
					  _countof(envOboeFrq20) , envOboeFrq20,
					  _countof(envOboeAmp21) , envOboeAmp21,
					  _countof(envOboeFrq21) , envOboeFrq21 };

PRT prtClar[21] = { _countof(envClarAmp01) , envClarAmp01,
					  _countof(envClarFrq01) , envClarFrq01,
					  _countof(envClarAmp02) , envClarAmp02,
					  _countof(envClarFrq02) , envClarFrq02,
					  _countof(envClarAmp03) , envClarAmp03,
					  _countof(envClarFrq03) , envClarFrq03,
					  _countof(envClarAmp04) , envClarAmp04,
					  _countof(envClarFrq04) , envClarFrq04,
					  _countof(envClarAmp05) , envClarAmp05,
					  _countof(envClarFrq05) , envClarFrq05,
					  _countof(envClarAmp06) , envClarAmp06,
					  _countof(envClarFrq06) , envClarFrq06,
					  _countof(envClarAmp07) , envClarAmp07,
					  _countof(envClarFrq07) , envClarFrq07,
					  _countof(envClarAmp08) , envClarAmp08,
					  _countof(envClarFrq08) , envClarFrq08,
					  _countof(envClarAmp09) , envClarAmp09,
					  _countof(envClarFrq09) , envClarFrq09,
					  _countof(envClarAmp10) , envClarAmp10,
					  _countof(envClarFrq10) , envClarFrq10,
					  _countof(envClarAmp11) , envClarAmp11,
					  _countof(envClarFrq11) , envClarFrq11,
					  _countof(envClarAmp12) , envClarAmp12,
					  _countof(envClarFrq12) , envClarFrq12,
					  _countof(envClarAmp13) , envClarAmp13,
					  _countof(envClarFrq13) , envClarFrq13,
					  _countof(envClarAmp14) , envClarAmp14,
					  _countof(envClarFrq14) , envClarFrq14,
					  _countof(envClarAmp15) , envClarAmp15,
					  _countof(envClarFrq15) , envClarFrq15,
					  _countof(envClarAmp16) , envClarAmp16,
					  _countof(envClarFrq16) , envClarFrq16,
					  _countof(envClarAmp17) , envClarAmp17,
					  _countof(envClarFrq17) , envClarFrq17,
					  _countof(envClarAmp18) , envClarAmp18,
					  _countof(envClarFrq18) , envClarFrq18,
					  _countof(envClarAmp19) , envClarAmp19,
					  _countof(envClarFrq19) , envClarFrq19,
					  _countof(envClarAmp20) , envClarAmp20,
					  _countof(envClarFrq20) , envClarFrq20,
					  _countof(envClarAmp21) , envClarAmp21,
					  _countof(envClarFrq21) , envClarFrq21 };

INS insTrum = { 360, 12, prtTrum };
INS insOboe = { 313, 21, prtOboe };
INS insClar = { 330, 21, prtClar };
