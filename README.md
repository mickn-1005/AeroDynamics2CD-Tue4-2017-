# CFD of Karman Vortex

　一様流の中の角柱周りのカルマン渦についてのCFDを行った。デカルト座標系での計算を行った。圧力場についてはPoisson方程式を逐次緩和法で解き、その後速度場を４次精度の風上差分法を用いて解いている。  
　計算結果について、以下の４つの場合を計算した。  
1. 角柱 (１辺１[m])を流れ場中に置いた時  
2. 1.の角柱の後流に同じ角柱を配置した時  
![karman_modify0](https://user-images.githubusercontent.com/28618623/35773254-a5e70b26-098f-11e8-88bf-4b622221cdad.gif)  
![karman_modify1](https://user-images.githubusercontent.com/28618623/35773255-bc617e36-098f-11e8-89f0-0fba78fb98e5.gif)  

3. 2.の角柱列に等間隔にさらに角柱を設置した時  
4. 1.の角柱の後流に同じ角柱２つを並べて置いた時  
![karman_modify3](https://user-images.githubusercontent.com/28618623/35773258-d41ee054-098f-11e8-8c64-656452a8c4b7.gif)  
![karman_modify2](https://user-images.githubusercontent.com/28618623/35773257-c7165f90-098f-11e8-94d7-6e61c7c61070.gif)  
