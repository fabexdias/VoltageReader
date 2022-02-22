% Todas as medições foram feitas com o polo negativo da fonte ligado ao
% conector que liga ao ground e com o polo positivo no respetivo conector
% de andar.

grau = 1; 
% Esta variavél indica o grau da função polinomial que vai 
% aproximar a relação entre variaveis. 
% Trata-se de um numero inteiro que percente ao intervalo: [0; +inf[.

% Andar 1: as tensões deste andar estão tipicamente entre 2 V e 4.2 V,
% conectou-se o leitor de tensões a uma fonte regulavél DC, e observou-se
% as tensões lidas.
y1 = 2:0.1:4.2;
% Incrementos de 0.1 V
x1 = [1.9550342559 2.0430107116 2.1065492630 2.2140762805 2.2971651554 2.3753664493 2.4682307243 2.5562071800 2.6539590358 2.7517106533 2.8592374801 2.9472141265 3.0498533248 3.1378300189 3.2404692173 3.3235580921 3.4213099479 3.5190615653 3.6217007637 3.7145650386 3.8025415420 3.9100685119 3.9882698059];
a1 = polyfit(x1,y1,grau);
% se "a1(1,1) = a" e "a1(1,2) = b" então "Valor_real = a * Valor_lido + b" 

% Andar 2: as tensões deste andar estão tipicamente entre 4 V e 8.4 V.
y2 = 4:0.1:8.4;
% Incrementos de 0.1 V
x2 = [3.8905181884 3.9980449676 4.0860214233 4.1837730407 4.2815251350 4.3792767524 4.4770283699 4.5747799873 4.6823067665 4.7800588607 4.8778104782 4.9755620956 5.0733137130 5.1612901687 5.2590422630 5.3763442039 5.4643206596 5.5620722770 5.6402735710 5.7478003501 5.8357772827 5.9335289001 6.0508308410 6.1388072967 6.2365589141 6.3343110084 6.4320626258 6.5298142433 6.6275658607 6.7253174781 6.8230695724 6.9305963516 7.0283479690 7.1163244247 7.2140760421 7.3216032981 7.4291300773 7.5073313713 7.6246333122 7.7223849296 7.8103618621 7.9081134796 8.0156402587 8.1133918762 8.2111434936];
a2 = polyfit(x2,y2,grau);

% Andar 3: as tensões deste andar estão tipicamente entre 6 V e 12.6 V
y3 = 6:0.2:12.6;
% Incrementos de 0.2 V
x3 = [5.8504400253 6.0557184219 6.2463340759 6.4369506835 6.6275663375 6.8328447341 7.0381231307 7.2287392616 7.3900294303 7.5953078269 7.7859234809 7.9765396118 8.1818180084 8.3870964050 8.5777120590 8.7829914093 8.9589443206 9.1642227172 9.3548383712 9.5601177215 9.7507333755 9.9413490295 10.1319646835 10.3372440338 10.5278587341 10.7184753417 10.9384164810 11.1143693923 11.3049850463 11.4956007003 11.6862173080 11.9061584472 12.0821113586 12.2727270126];
a3 = polyfit(x3,y3,grau);

% Andar 4: as tensões deste andar estão tipicamente entre 8 V e 16.8 V
y4 = 8:0.4:16.8;
% Incrementos de 0.4 V
x4 = [7.7218961715 8.1094818115 8.4970674514 8.8846530914 9.2722377777 9.6598243713 10.0474090576 10.4349956512 10.8225803375 11.2399806976 11.6275653839 11.9853372573 12.3729219436 12.7605075836 13.1779088973 13.5953083038 13.9530782699 14.3406639099 14.7282505035 15.1158361434 15.4736061096 15.8611917495 16.2487792968];
a4 = polyfit(x4,y4,grau);

% Andar 5: as tensões deste andar estão tipicamente entre 10 V e 21 V
y5 = 10:0.5:21;
% Incrementos de 0.5 V
x5 = [9.7790813446 10.2561092376 10.7629518508 11.2101659774 11.7170085906 12.2238512039 12.7306928634 13.2077226638 13.7145652770 14.1617784500 14.6686220169 15.1456499099 15.6823062896 16.1295223236 16.6661777496 17.1432056427 17.5904216766 18.1270771026 18.5742912292 19.0513191223 19.6774196624 20.1544475555 20.6016597747];
a5 = polyfit(x5,y5,grau);

% Andar 6: as tensões deste andar estão tipicamente entre 12 V e 25.2 V
y6 = 12:0.6:25.2;
% Incrementos de 0.6 V
x6 = [11.7170085906 12.2834796905 12.8797645568 13.4462366104 14.0723352432 14.6686220169 15.2350931167 15.8611917495 16.3978500366 17.0239486694 17.5606060028 18.1568908691 18.7233619689 19.2898349761 19.9755611419 20.5122184753 21.0190620422 21.6451606750 22.3010749816 22.9271736145 23.4936447143 24.0601177215 24.6862163543];
a6 = polyfit(x6,y6,grau);


% Código para saber a melhor aproximação - calculo de R^2
sstot = zeros(1,6);
ssres = zeros(1,6);
rsquared = zeros(1,6);

polydata1 = polyval(a1,x1);
sstot(1,1) = sum((y1 - mean(y1)).^2);
ssres(1,1) = sum((y1 - polydata1).^2);
rsquared(1,1) = 1 - (ssres(1,1) / sstot(1,1));

polydata2 = polyval(a2,x2);
sstot(1,2) = sum((y2 - mean(y2)).^2);
ssres(1,2) = sum((y2 - polydata2).^2);
rsquared(1,2) = 1 - (ssres(1,2) / sstot(1,2));

polydata3 = polyval(a3,x3);
sstot(1,3) = sum((y3 - mean(y3)).^2);
ssres(1,3) = sum((y3 - polydata3).^2);
rsquared(1,3) = 1 - (ssres(1,3) / sstot(1,3));

polydata4 = polyval(a4,x4);
sstot(1,4) = sum((y4 - mean(y4)).^2);
ssres(1,4) = sum((y4 - polydata4).^2);
rsquared(1,4) = 1 - (ssres(1,4) / sstot(1,4));

polydata5 = polyval(a5,x5);
sstot(1,5) = sum((y5 - mean(y5)).^2);
ssres(1,5) = sum((y5 - polydata5).^2);
rsquared(1,5) = 1 - (ssres(1,5) / sstot(1,5));

polydata6 = polyval(a6,x6);
sstot(1,6) = sum((y6 - mean(y6)).^2);
ssres(1,6) = sum((y6 - polydata6).^2);
rsquared(1,6) = 1 - (ssres(1,6) / sstot(1,6));
% Soma dos R^2 para grau 1 = 5.99925903494116
% Soma dos R^2 para grau 2 = 5.99950453778493