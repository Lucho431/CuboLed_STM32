(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: placaCub-Edge_Cuts.gbr_cutout_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Thursday, 07 April 2022 at 10:36)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)

(TOOL DIAMETER: 1.0 mm)
(Feedrate_XY: 240.0 mm/min)
(Feedrate_Z: 120.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -1.8 mm)
(DepthPerCut: 0.6 mm <=>3 passes)
(Z_Move: 5.0 mm)
(Z Start: None mm)
(Z End: 45.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Geometry: default)

(X range:    0.4750 ...  134.3130  mm)
(Y range:    0.8590 ...  171.7810  mm)

(Spindle Speed: 24000.0 RPM)
G21
G90
G94

G01 F240.00

M5
G00 Z15.0000
G00 X0.0000 Y0.0000
T1
M6    
(MSG, Change to Tool Dia = 1.0000)
M0
G00 Z15.0000

M03 S24000.0
G01 F240.00
G00 X7.8972 Y4.1480
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X7.9273 Y4.1300
G01 X7.9551 Y4.1143
G01 X7.9814 Y4.1011
G01 X8.0701 Y4.0591
G01 X8.0970 Y4.0472
G01 X8.1268 Y4.0356
G01 X8.2192 Y4.0026
G01 X8.2471 Y3.9933
G01 X8.2778 Y3.9848
G01 X8.3730 Y3.9609
G01 X8.4018 Y3.9545
G01 X8.4332 Y3.9490
G01 X8.5303 Y3.9346
G01 X8.5595 Y3.9310
G01 X8.5913 Y3.9286
G01 X8.6893 Y3.9237
G01 X8.7188 Y3.9230
G01 X8.7507 Y3.9237
G01 X8.8487 Y3.9286
G01 X8.8781 Y3.9307
G01 X8.9097 Y3.9346
G01 X9.0068 Y3.9490
G01 X9.0358 Y3.9540
G01 X9.0670 Y3.9609
G01 X9.1622 Y3.9848
G01 X9.1905 Y3.9926
G01 X9.2208 Y4.0026
G01 X9.3132 Y4.0356
G01 X9.3430 Y4.0472
G01 X9.3699 Y4.0591
G01 X9.4586 Y4.1011
G01 X9.4849 Y4.1143
G01 X9.5127 Y4.1300
G01 X9.5428 Y4.1480
G00 X9.5428 Y4.1480
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X9.5127 Y4.1300
G01 X9.4849 Y4.1143
G01 X9.4586 Y4.1011
G01 X9.3699 Y4.0591
G01 X9.3430 Y4.0472
G01 X9.3132 Y4.0356
G01 X9.2208 Y4.0026
G01 X9.1905 Y3.9926
G01 X9.1622 Y3.9848
G01 X9.0670 Y3.9609
G01 X9.0358 Y3.9540
G01 X9.0068 Y3.9490
G01 X8.9097 Y3.9346
G01 X8.8781 Y3.9307
G01 X8.8487 Y3.9286
G01 X8.7507 Y3.9237
G01 X8.7188 Y3.9230
G01 X8.6893 Y3.9237
G01 X8.5913 Y3.9286
G01 X8.5595 Y3.9310
G01 X8.5303 Y3.9346
G01 X8.4332 Y3.9490
G01 X8.4018 Y3.9545
G01 X8.3730 Y3.9609
G01 X8.2778 Y3.9848
G01 X8.2471 Y3.9933
G01 X8.2192 Y4.0026
G01 X8.1268 Y4.0356
G01 X8.0970 Y4.0472
G01 X8.0701 Y4.0591
G01 X7.9814 Y4.1011
G01 X7.9551 Y4.1143
G01 X7.9273 Y4.1300
G01 X7.8972 Y4.1480
G00 X7.8972 Y4.1480
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X7.9273 Y4.1300
G01 X7.9551 Y4.1143
G01 X7.9814 Y4.1011
G01 X8.0701 Y4.0591
G01 X8.0970 Y4.0472
G01 X8.1268 Y4.0356
G01 X8.2192 Y4.0026
G01 X8.2471 Y3.9933
G01 X8.2778 Y3.9848
G01 X8.3730 Y3.9609
G01 X8.4018 Y3.9545
G01 X8.4332 Y3.9490
G01 X8.5303 Y3.9346
G01 X8.5595 Y3.9310
G01 X8.5913 Y3.9286
G01 X8.6893 Y3.9237
G01 X8.7188 Y3.9230
G01 X8.7507 Y3.9237
G01 X8.8487 Y3.9286
G01 X8.8781 Y3.9307
G01 X8.9097 Y3.9346
G01 X9.0068 Y3.9490
G01 X9.0358 Y3.9540
G01 X9.0670 Y3.9609
G01 X9.1622 Y3.9848
G01 X9.1905 Y3.9926
G01 X9.2208 Y4.0026
G01 X9.3132 Y4.0356
G01 X9.3430 Y4.0472
G01 X9.3699 Y4.0591
G01 X9.4586 Y4.1011
G01 X9.4849 Y4.1143
G01 X9.5127 Y4.1300
G01 X9.5428 Y4.1480
G00 Z5.0000
G00 X8.4397 Y7.1480
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X8.5303 Y7.1614
G01 X8.5619 Y7.1653
G01 X8.5913 Y7.1674
G01 X8.6893 Y7.1723
G01 X8.7212 Y7.1730
G01 X8.7507 Y7.1723
G01 X8.8487 Y7.1674
G01 X8.8781 Y7.1653
G01 X8.9097 Y7.1614
G01 X9.0003 Y7.1480
G00 X9.0003 Y7.1480
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X8.9097 Y7.1614
G01 X8.8781 Y7.1653
G01 X8.8487 Y7.1674
G01 X8.7507 Y7.1723
G01 X8.7212 Y7.1730
G01 X8.6893 Y7.1723
G01 X8.5913 Y7.1674
G01 X8.5619 Y7.1653
G01 X8.5303 Y7.1614
G01 X8.4397 Y7.1480
G00 X8.4397 Y7.1480
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X8.5303 Y7.1614
G01 X8.5619 Y7.1653
G01 X8.5913 Y7.1674
G01 X8.6893 Y7.1723
G01 X8.7212 Y7.1730
G01 X8.7507 Y7.1723
G01 X8.8487 Y7.1674
G01 X8.8781 Y7.1653
G01 X8.9097 Y7.1614
G01 X9.0003 Y7.1480
G00 Z5.0000
G00 X0.7245 Y84.9200
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X0.4750 Y6.5660
G01 X0.4758 Y6.5331
G01 X0.4779 Y6.5037
G01 X0.4818 Y6.4721
G01 X0.4868 Y6.4430
G01 X0.4938 Y6.4120
G01 X0.5016 Y6.3835
G01 X0.5108 Y6.3555
G01 X0.5222 Y6.3258
G01 X0.5341 Y6.2988
G01 X0.5483 Y6.2702
G01 X0.5640 Y6.2425
G01 X0.5798 Y6.2176
G01 X0.5967 Y6.1935
G01 X0.6162 Y6.1683
G01 X0.6355 Y6.1459
G01 X0.6573 Y6.1228
G01 X5.7380 Y1.0420
G01 X5.7612 Y1.0201
G01 X5.8087 Y0.9813
G01 X5.8597 Y0.9473
G01 X5.9139 Y0.9185
G01 X5.9706 Y0.8951
G01 X6.0293 Y0.8774
G01 X6.0895 Y0.8656
G01 X6.1481 Y0.8598
G01 X6.1800 Y0.8590
G01 X128.6080 Y0.8590
G01 X128.6399 Y0.8598
G01 X128.6985 Y0.8656
G01 X128.7610 Y0.8780
G01 X128.8197 Y0.8960
G01 X128.8741 Y0.9185
G01 X128.9304 Y0.9486
G01 X128.9813 Y0.9827
G01 X129.0268 Y1.0201
G01 X129.0500 Y1.0420
G01 X134.1300 Y6.1220
G01 X134.1519 Y6.1452
G01 X134.1907 Y6.1927
G01 X134.2247 Y6.2437
G01 X134.2535 Y6.2979
G01 X134.2760 Y6.3523
G01 X134.2940 Y6.4110
G01 X134.3060 Y6.4711
G01 X134.3122 Y6.5321
G01 X134.3130 Y6.5640
G01 X134.3130 Y84.9200
G00 X134.3130 Y84.9200
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X134.3130 Y6.5640
G01 X134.3122 Y6.5321
G01 X134.3060 Y6.4711
G01 X134.2940 Y6.4110
G01 X134.2760 Y6.3523
G01 X134.2535 Y6.2979
G01 X134.2247 Y6.2437
G01 X134.1907 Y6.1927
G01 X134.1519 Y6.1452
G01 X134.1300 Y6.1220
G01 X129.0500 Y1.0420
G01 X129.0268 Y1.0201
G01 X128.9813 Y0.9827
G01 X128.9304 Y0.9486
G01 X128.8741 Y0.9185
G01 X128.8197 Y0.8960
G01 X128.7610 Y0.8780
G01 X128.6985 Y0.8656
G01 X128.6399 Y0.8598
G01 X128.6080 Y0.8590
G01 X6.1800 Y0.8590
G01 X6.1481 Y0.8598
G01 X6.0895 Y0.8656
G01 X6.0293 Y0.8774
G01 X5.9706 Y0.8951
G01 X5.9139 Y0.9185
G01 X5.8597 Y0.9473
G01 X5.8087 Y0.9813
G01 X5.7612 Y1.0201
G01 X5.7380 Y1.0420
G01 X0.6573 Y6.1228
G01 X0.6355 Y6.1459
G01 X0.6162 Y6.1683
G01 X0.5967 Y6.1935
G01 X0.5798 Y6.2176
G01 X0.5640 Y6.2425
G01 X0.5483 Y6.2702
G01 X0.5341 Y6.2988
G01 X0.5222 Y6.3258
G01 X0.5108 Y6.3555
G01 X0.5016 Y6.3835
G01 X0.4938 Y6.4120
G01 X0.4868 Y6.4430
G01 X0.4818 Y6.4721
G01 X0.4779 Y6.5037
G01 X0.4758 Y6.5331
G01 X0.4750 Y6.5660
G01 X0.7245 Y84.9200
G00 X0.7245 Y84.9200
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X0.4750 Y6.5660
G01 X0.4758 Y6.5331
G01 X0.4779 Y6.5037
G01 X0.4818 Y6.4721
G01 X0.4868 Y6.4430
G01 X0.4938 Y6.4120
G01 X0.5016 Y6.3835
G01 X0.5108 Y6.3555
G01 X0.5222 Y6.3258
G01 X0.5341 Y6.2988
G01 X0.5483 Y6.2702
G01 X0.5640 Y6.2425
G01 X0.5798 Y6.2176
G01 X0.5967 Y6.1935
G01 X0.6162 Y6.1683
G01 X0.6355 Y6.1459
G01 X0.6573 Y6.1228
G01 X5.7380 Y1.0420
G01 X5.7612 Y1.0201
G01 X5.8087 Y0.9813
G01 X5.8597 Y0.9473
G01 X5.9139 Y0.9185
G01 X5.9706 Y0.8951
G01 X6.0293 Y0.8774
G01 X6.0895 Y0.8656
G01 X6.1481 Y0.8598
G01 X6.1800 Y0.8590
G01 X128.6080 Y0.8590
G01 X128.6399 Y0.8598
G01 X128.6985 Y0.8656
G01 X128.7610 Y0.8780
G01 X128.8197 Y0.8960
G01 X128.8741 Y0.9185
G01 X128.9304 Y0.9486
G01 X128.9813 Y0.9827
G01 X129.0268 Y1.0201
G01 X129.0500 Y1.0420
G01 X134.1300 Y6.1220
G01 X134.1519 Y6.1452
G01 X134.1907 Y6.1927
G01 X134.2247 Y6.2437
G01 X134.2535 Y6.2979
G01 X134.2760 Y6.3523
G01 X134.2940 Y6.4110
G01 X134.3060 Y6.4711
G01 X134.3122 Y6.5321
G01 X134.3130 Y6.5640
G01 X134.3130 Y84.9200
G00 Z5.0000
G00 X0.7341 Y87.9200
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X0.9830 Y166.0780
G01 X0.9839 Y166.1088
G01 X0.9861 Y166.1383
G01 X0.9901 Y166.1699
G01 X0.9952 Y166.1989
G01 X1.0023 Y166.2300
G01 X1.0102 Y166.2584
G01 X1.0195 Y166.2864
G01 X1.0309 Y166.3161
G01 X1.0429 Y166.3430
G01 X1.0573 Y166.3715
G01 X1.0731 Y166.3992
G01 X1.0889 Y166.4241
G01 X1.1059 Y166.4481
G01 X1.1255 Y166.4732
G01 X1.1448 Y166.4956
G01 X1.1660 Y166.5180
G01 X6.2460 Y171.5980
G01 X6.2692 Y171.6199
G01 X6.3147 Y171.6573
G01 X6.3656 Y171.6914
G01 X6.4219 Y171.7215
G01 X6.4763 Y171.7440
G01 X6.5350 Y171.7620
G01 X6.5975 Y171.7744
G01 X6.6561 Y171.7802
G01 X6.6880 Y171.7810
G01 X128.6080 Y171.7810
G01 X128.6399 Y171.7802
G01 X128.6985 Y171.7744
G01 X128.7587 Y171.7626
G01 X128.8174 Y171.7449
G01 X128.8741 Y171.7215
G01 X128.9283 Y171.6927
G01 X128.9793 Y171.6587
G01 X129.0268 Y171.6199
G01 X129.0500 Y171.5980
G01 X134.1300 Y166.5180
G01 X134.1519 Y166.4948
G01 X134.1907 Y166.4473
G01 X134.2247 Y166.3963
G01 X134.2535 Y166.3421
G01 X134.2769 Y166.2854
G01 X134.2946 Y166.2267
G01 X134.3060 Y166.1689
G01 X134.3122 Y166.1079
G01 X134.3130 Y166.0760
G01 X134.3130 Y87.9200
G00 X134.3130 Y87.9200
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X134.3130 Y166.0760
G01 X134.3122 Y166.1079
G01 X134.3060 Y166.1689
G01 X134.2946 Y166.2267
G01 X134.2769 Y166.2854
G01 X134.2535 Y166.3421
G01 X134.2247 Y166.3963
G01 X134.1907 Y166.4473
G01 X134.1519 Y166.4948
G01 X134.1300 Y166.5180
G01 X129.0500 Y171.5980
G01 X129.0268 Y171.6199
G01 X128.9793 Y171.6587
G01 X128.9283 Y171.6927
G01 X128.8741 Y171.7215
G01 X128.8174 Y171.7449
G01 X128.7587 Y171.7626
G01 X128.6985 Y171.7744
G01 X128.6399 Y171.7802
G01 X128.6080 Y171.7810
G01 X6.6880 Y171.7810
G01 X6.6561 Y171.7802
G01 X6.5975 Y171.7744
G01 X6.5350 Y171.7620
G01 X6.4763 Y171.7440
G01 X6.4219 Y171.7215
G01 X6.3656 Y171.6914
G01 X6.3147 Y171.6573
G01 X6.2692 Y171.6199
G01 X6.2460 Y171.5980
G01 X1.1660 Y166.5180
G01 X1.1448 Y166.4956
G01 X1.1255 Y166.4732
G01 X1.1059 Y166.4481
G01 X1.0889 Y166.4241
G01 X1.0731 Y166.3992
G01 X1.0573 Y166.3715
G01 X1.0429 Y166.3430
G01 X1.0309 Y166.3161
G01 X1.0195 Y166.2864
G01 X1.0102 Y166.2584
G01 X1.0023 Y166.2300
G01 X0.9952 Y166.1989
G01 X0.9901 Y166.1699
G01 X0.9861 Y166.1383
G01 X0.9839 Y166.1088
G01 X0.9830 Y166.0780
G01 X0.7341 Y87.9200
G00 X0.7341 Y87.9200
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X0.9830 Y166.0780
G01 X0.9839 Y166.1088
G01 X0.9861 Y166.1383
G01 X0.9901 Y166.1699
G01 X0.9952 Y166.1989
G01 X1.0023 Y166.2300
G01 X1.0102 Y166.2584
G01 X1.0195 Y166.2864
G01 X1.0309 Y166.3161
G01 X1.0429 Y166.3430
G01 X1.0573 Y166.3715
G01 X1.0731 Y166.3992
G01 X1.0889 Y166.4241
G01 X1.1059 Y166.4481
G01 X1.1255 Y166.4732
G01 X1.1448 Y166.4956
G01 X1.1660 Y166.5180
G01 X6.2460 Y171.5980
G01 X6.2692 Y171.6199
G01 X6.3147 Y171.6573
G01 X6.3656 Y171.6914
G01 X6.4219 Y171.7215
G01 X6.4763 Y171.7440
G01 X6.5350 Y171.7620
G01 X6.5975 Y171.7744
G01 X6.6561 Y171.7802
G01 X6.6880 Y171.7810
G01 X128.6080 Y171.7810
G01 X128.6399 Y171.7802
G01 X128.6985 Y171.7744
G01 X128.7587 Y171.7626
G01 X128.8174 Y171.7449
G01 X128.8741 Y171.7215
G01 X128.9283 Y171.6927
G01 X128.9793 Y171.6587
G01 X129.0268 Y171.6199
G01 X129.0500 Y171.5980
G01 X134.1300 Y166.5180
G01 X134.1519 Y166.4948
G01 X134.1907 Y166.4473
G01 X134.2247 Y166.3963
G01 X134.2535 Y166.3421
G01 X134.2769 Y166.2854
G01 X134.2946 Y166.2267
G01 X134.3060 Y166.1689
G01 X134.3122 Y166.1079
G01 X134.3130 Y166.0760
G01 X134.3130 Y87.9200
G00 Z5.0000
G00 X127.3988 Y165.6920
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X127.3687 Y165.6740
G01 X127.3409 Y165.6583
G01 X127.3146 Y165.6451
G01 X127.2259 Y165.6031
G01 X127.1990 Y165.5912
G01 X127.1692 Y165.5796
G01 X127.0768 Y165.5466
G01 X127.0465 Y165.5366
G01 X127.0182 Y165.5288
G01 X126.9230 Y165.5049
G01 X126.8918 Y165.4980
G01 X126.8628 Y165.4930
G01 X126.7657 Y165.4786
G01 X126.7341 Y165.4747
G01 X126.7047 Y165.4726
G01 X126.6067 Y165.4677
G01 X126.5748 Y165.4670
G01 X126.5453 Y165.4677
G01 X126.4473 Y165.4726
G01 X126.4155 Y165.4750
G01 X126.3863 Y165.4786
G01 X126.2892 Y165.4930
G01 X126.2578 Y165.4985
G01 X126.2290 Y165.5049
G01 X126.1338 Y165.5288
G01 X126.1031 Y165.5373
G01 X126.0752 Y165.5466
G01 X125.9828 Y165.5796
G01 X125.9530 Y165.5912
G01 X125.9261 Y165.6031
G01 X125.8374 Y165.6451
G01 X125.8111 Y165.6583
G01 X125.7833 Y165.6740
G01 X125.7532 Y165.6920
G00 X125.7532 Y165.6920
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X125.7833 Y165.6740
G01 X125.8111 Y165.6583
G01 X125.8374 Y165.6451
G01 X125.9261 Y165.6031
G01 X125.9530 Y165.5912
G01 X125.9828 Y165.5796
G01 X126.0752 Y165.5466
G01 X126.1031 Y165.5373
G01 X126.1338 Y165.5288
G01 X126.2290 Y165.5049
G01 X126.2578 Y165.4985
G01 X126.2892 Y165.4930
G01 X126.3863 Y165.4786
G01 X126.4155 Y165.4750
G01 X126.4473 Y165.4726
G01 X126.5453 Y165.4677
G01 X126.5748 Y165.4670
G01 X126.6067 Y165.4677
G01 X126.7047 Y165.4726
G01 X126.7341 Y165.4747
G01 X126.7657 Y165.4786
G01 X126.8628 Y165.4930
G01 X126.8918 Y165.4980
G01 X126.9230 Y165.5049
G01 X127.0182 Y165.5288
G01 X127.0465 Y165.5366
G01 X127.0768 Y165.5466
G01 X127.1692 Y165.5796
G01 X127.1990 Y165.5912
G01 X127.2259 Y165.6031
G01 X127.3146 Y165.6451
G01 X127.3409 Y165.6583
G01 X127.3687 Y165.6740
G01 X127.3988 Y165.6920
G00 X127.3988 Y165.6920
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X127.3687 Y165.6740
G01 X127.3409 Y165.6583
G01 X127.3146 Y165.6451
G01 X127.2259 Y165.6031
G01 X127.1990 Y165.5912
G01 X127.1692 Y165.5796
G01 X127.0768 Y165.5466
G01 X127.0465 Y165.5366
G01 X127.0182 Y165.5288
G01 X126.9230 Y165.5049
G01 X126.8918 Y165.4980
G01 X126.8628 Y165.4930
G01 X126.7657 Y165.4786
G01 X126.7341 Y165.4747
G01 X126.7047 Y165.4726
G01 X126.6067 Y165.4677
G01 X126.5748 Y165.4670
G01 X126.5453 Y165.4677
G01 X126.4473 Y165.4726
G01 X126.4155 Y165.4750
G01 X126.3863 Y165.4786
G01 X126.2892 Y165.4930
G01 X126.2578 Y165.4985
G01 X126.2290 Y165.5049
G01 X126.1338 Y165.5288
G01 X126.1031 Y165.5373
G01 X126.0752 Y165.5466
G01 X125.9828 Y165.5796
G01 X125.9530 Y165.5912
G01 X125.9261 Y165.6031
G01 X125.8374 Y165.6451
G01 X125.8111 Y165.6583
G01 X125.7833 Y165.6740
G01 X125.7532 Y165.6920
G00 Z5.0000
G00 X126.2957 Y168.6920
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X126.3863 Y168.7054
G01 X126.4179 Y168.7093
G01 X126.4473 Y168.7114
G01 X126.5453 Y168.7163
G01 X126.5772 Y168.7170
G01 X126.6067 Y168.7163
G01 X126.7047 Y168.7114
G01 X126.7341 Y168.7093
G01 X126.7657 Y168.7054
G01 X126.8563 Y168.6920
G00 X126.8563 Y168.6920
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X126.7657 Y168.7054
G01 X126.7341 Y168.7093
G01 X126.7047 Y168.7114
G01 X126.6067 Y168.7163
G01 X126.5772 Y168.7170
G01 X126.5453 Y168.7163
G01 X126.4473 Y168.7114
G01 X126.4179 Y168.7093
G01 X126.3863 Y168.7054
G01 X126.2957 Y168.6920
G00 X126.2957 Y168.6920
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X126.3863 Y168.7054
G01 X126.4179 Y168.7093
G01 X126.4473 Y168.7114
G01 X126.5453 Y168.7163
G01 X126.5772 Y168.7170
G01 X126.6067 Y168.7163
G01 X126.7047 Y168.7114
G01 X126.7341 Y168.7093
G01 X126.7657 Y168.7054
G01 X126.8563 Y168.6920
G00 Z5.0000
G00 X9.5428 Y165.6920
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X9.5127 Y165.6740
G01 X9.4849 Y165.6583
G01 X9.4586 Y165.6451
G01 X9.3699 Y165.6031
G01 X9.3430 Y165.5912
G01 X9.3132 Y165.5796
G01 X9.2208 Y165.5466
G01 X9.1905 Y165.5366
G01 X9.1622 Y165.5288
G01 X9.0670 Y165.5049
G01 X9.0358 Y165.4980
G01 X9.0068 Y165.4930
G01 X8.9097 Y165.4786
G01 X8.8781 Y165.4747
G01 X8.8487 Y165.4726
G01 X8.7507 Y165.4677
G01 X8.7188 Y165.4670
G01 X8.6893 Y165.4677
G01 X8.5913 Y165.4726
G01 X8.5595 Y165.4750
G01 X8.5303 Y165.4786
G01 X8.4332 Y165.4930
G01 X8.4018 Y165.4985
G01 X8.3730 Y165.5049
G01 X8.2778 Y165.5288
G01 X8.2471 Y165.5373
G01 X8.2192 Y165.5466
G01 X8.1268 Y165.5796
G01 X8.0970 Y165.5912
G01 X8.0701 Y165.6031
G01 X7.9814 Y165.6451
G01 X7.9551 Y165.6583
G01 X7.9273 Y165.6740
G01 X7.8972 Y165.6920
G00 X7.8972 Y165.6920
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X7.9273 Y165.6740
G01 X7.9551 Y165.6583
G01 X7.9814 Y165.6451
G01 X8.0701 Y165.6031
G01 X8.0970 Y165.5912
G01 X8.1268 Y165.5796
G01 X8.2192 Y165.5466
G01 X8.2471 Y165.5373
G01 X8.2778 Y165.5288
G01 X8.3730 Y165.5049
G01 X8.4018 Y165.4985
G01 X8.4332 Y165.4930
G01 X8.5303 Y165.4786
G01 X8.5595 Y165.4750
G01 X8.5913 Y165.4726
G01 X8.6893 Y165.4677
G01 X8.7188 Y165.4670
G01 X8.7507 Y165.4677
G01 X8.8487 Y165.4726
G01 X8.8781 Y165.4747
G01 X8.9097 Y165.4786
G01 X9.0068 Y165.4930
G01 X9.0358 Y165.4980
G01 X9.0670 Y165.5049
G01 X9.1622 Y165.5288
G01 X9.1905 Y165.5366
G01 X9.2208 Y165.5466
G01 X9.3132 Y165.5796
G01 X9.3430 Y165.5912
G01 X9.3699 Y165.6031
G01 X9.4586 Y165.6451
G01 X9.4849 Y165.6583
G01 X9.5127 Y165.6740
G01 X9.5428 Y165.6920
G00 X9.5428 Y165.6920
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X9.5127 Y165.6740
G01 X9.4849 Y165.6583
G01 X9.4586 Y165.6451
G01 X9.3699 Y165.6031
G01 X9.3430 Y165.5912
G01 X9.3132 Y165.5796
G01 X9.2208 Y165.5466
G01 X9.1905 Y165.5366
G01 X9.1622 Y165.5288
G01 X9.0670 Y165.5049
G01 X9.0358 Y165.4980
G01 X9.0068 Y165.4930
G01 X8.9097 Y165.4786
G01 X8.8781 Y165.4747
G01 X8.8487 Y165.4726
G01 X8.7507 Y165.4677
G01 X8.7188 Y165.4670
G01 X8.6893 Y165.4677
G01 X8.5913 Y165.4726
G01 X8.5595 Y165.4750
G01 X8.5303 Y165.4786
G01 X8.4332 Y165.4930
G01 X8.4018 Y165.4985
G01 X8.3730 Y165.5049
G01 X8.2778 Y165.5288
G01 X8.2471 Y165.5373
G01 X8.2192 Y165.5466
G01 X8.1268 Y165.5796
G01 X8.0970 Y165.5912
G01 X8.0701 Y165.6031
G01 X7.9814 Y165.6451
G01 X7.9551 Y165.6583
G01 X7.9273 Y165.6740
G01 X7.8972 Y165.6920
G00 Z5.0000
G00 X8.4397 Y168.6920
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X8.5303 Y168.7054
G01 X8.5619 Y168.7093
G01 X8.5913 Y168.7114
G01 X8.6893 Y168.7163
G01 X8.7212 Y168.7170
G01 X8.7507 Y168.7163
G01 X8.8487 Y168.7114
G01 X8.8781 Y168.7093
G01 X8.9097 Y168.7054
G01 X9.0003 Y168.6920
G00 X9.0003 Y168.6920
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X8.9097 Y168.7054
G01 X8.8781 Y168.7093
G01 X8.8487 Y168.7114
G01 X8.7507 Y168.7163
G01 X8.7212 Y168.7170
G01 X8.6893 Y168.7163
G01 X8.5913 Y168.7114
G01 X8.5619 Y168.7093
G01 X8.5303 Y168.7054
G01 X8.4397 Y168.6920
G00 X8.4397 Y168.6920
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X8.5303 Y168.7054
G01 X8.5619 Y168.7093
G01 X8.5913 Y168.7114
G01 X8.6893 Y168.7163
G01 X8.7212 Y168.7170
G01 X8.7507 Y168.7163
G01 X8.8487 Y168.7114
G01 X8.8781 Y168.7093
G01 X8.9097 Y168.7054
G01 X9.0003 Y168.6920
G00 Z5.0000
G00 X126.2957 Y7.1480
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X126.3863 Y7.1614
G01 X126.4179 Y7.1653
G01 X126.4473 Y7.1674
G01 X126.5453 Y7.1723
G01 X126.5772 Y7.1730
G01 X126.6067 Y7.1723
G01 X126.7047 Y7.1674
G01 X126.7341 Y7.1653
G01 X126.7657 Y7.1614
G01 X126.8563 Y7.1480
G00 X126.8563 Y7.1480
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X126.7657 Y7.1614
G01 X126.7341 Y7.1653
G01 X126.7047 Y7.1674
G01 X126.6067 Y7.1723
G01 X126.5772 Y7.1730
G01 X126.5453 Y7.1723
G01 X126.4473 Y7.1674
G01 X126.4179 Y7.1653
G01 X126.3863 Y7.1614
G01 X126.2957 Y7.1480
G00 X126.2957 Y7.1480
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X126.3863 Y7.1614
G01 X126.4179 Y7.1653
G01 X126.4473 Y7.1674
G01 X126.5453 Y7.1723
G01 X126.5772 Y7.1730
G01 X126.6067 Y7.1723
G01 X126.7047 Y7.1674
G01 X126.7341 Y7.1653
G01 X126.7657 Y7.1614
G01 X126.8563 Y7.1480
G00 Z5.0000
G00 X127.3988 Y4.1480
G01 F120.00
G01 Z-0.6000
G01 F240.00
G01 X127.3687 Y4.1300
G01 X127.3409 Y4.1143
G01 X127.3146 Y4.1011
G01 X127.2259 Y4.0591
G01 X127.1990 Y4.0472
G01 X127.1692 Y4.0356
G01 X127.0768 Y4.0026
G01 X127.0465 Y3.9926
G01 X127.0182 Y3.9848
G01 X126.9230 Y3.9609
G01 X126.8918 Y3.9540
G01 X126.8628 Y3.9490
G01 X126.7657 Y3.9346
G01 X126.7341 Y3.9307
G01 X126.7047 Y3.9286
G01 X126.6067 Y3.9237
G01 X126.5748 Y3.9230
G01 X126.5453 Y3.9237
G01 X126.4473 Y3.9286
G01 X126.4155 Y3.9310
G01 X126.3863 Y3.9346
G01 X126.2892 Y3.9490
G01 X126.2578 Y3.9545
G01 X126.2290 Y3.9609
G01 X126.1338 Y3.9848
G01 X126.1031 Y3.9933
G01 X126.0752 Y4.0026
G01 X125.9828 Y4.0356
G01 X125.9530 Y4.0472
G01 X125.9261 Y4.0591
G01 X125.8374 Y4.1011
G01 X125.8111 Y4.1143
G01 X125.7833 Y4.1300
G01 X125.7532 Y4.1480
G00 X125.7532 Y4.1480
G01 F120.00
G01 Z-1.2000
G01 F240.00
G01 X125.7833 Y4.1300
G01 X125.8111 Y4.1143
G01 X125.8374 Y4.1011
G01 X125.9261 Y4.0591
G01 X125.9530 Y4.0472
G01 X125.9828 Y4.0356
G01 X126.0752 Y4.0026
G01 X126.1031 Y3.9933
G01 X126.1338 Y3.9848
G01 X126.2290 Y3.9609
G01 X126.2578 Y3.9545
G01 X126.2892 Y3.9490
G01 X126.3863 Y3.9346
G01 X126.4155 Y3.9310
G01 X126.4473 Y3.9286
G01 X126.5453 Y3.9237
G01 X126.5748 Y3.9230
G01 X126.6067 Y3.9237
G01 X126.7047 Y3.9286
G01 X126.7341 Y3.9307
G01 X126.7657 Y3.9346
G01 X126.8628 Y3.9490
G01 X126.8918 Y3.9540
G01 X126.9230 Y3.9609
G01 X127.0182 Y3.9848
G01 X127.0465 Y3.9926
G01 X127.0768 Y4.0026
G01 X127.1692 Y4.0356
G01 X127.1990 Y4.0472
G01 X127.2259 Y4.0591
G01 X127.3146 Y4.1011
G01 X127.3409 Y4.1143
G01 X127.3687 Y4.1300
G01 X127.3988 Y4.1480
G00 X127.3988 Y4.1480
G01 F120.00
G01 Z-1.8000
G01 F240.00
G01 X127.3687 Y4.1300
G01 X127.3409 Y4.1143
G01 X127.3146 Y4.1011
G01 X127.2259 Y4.0591
G01 X127.1990 Y4.0472
G01 X127.1692 Y4.0356
G01 X127.0768 Y4.0026
G01 X127.0465 Y3.9926
G01 X127.0182 Y3.9848
G01 X126.9230 Y3.9609
G01 X126.8918 Y3.9540
G01 X126.8628 Y3.9490
G01 X126.7657 Y3.9346
G01 X126.7341 Y3.9307
G01 X126.7047 Y3.9286
G01 X126.6067 Y3.9237
G01 X126.5748 Y3.9230
G01 X126.5453 Y3.9237
G01 X126.4473 Y3.9286
G01 X126.4155 Y3.9310
G01 X126.3863 Y3.9346
G01 X126.2892 Y3.9490
G01 X126.2578 Y3.9545
G01 X126.2290 Y3.9609
G01 X126.1338 Y3.9848
G01 X126.1031 Y3.9933
G01 X126.0752 Y4.0026
G01 X125.9828 Y4.0356
G01 X125.9530 Y4.0472
G01 X125.9261 Y4.0591
G01 X125.8374 Y4.1011
G01 X125.8111 Y4.1143
G01 X125.7833 Y4.1300
G01 X125.7532 Y4.1480
G00 Z5.0000
M05
G00 Z5.0000
G00 Z45.00

