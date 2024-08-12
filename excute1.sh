#!/bin/bash

# 备份原始文件
cp src/DetectorConstruction.cc src/DetectorConstruction.cc.bak
cp include/constants.hh include/constants.hh.bak

# 修改文件
sed -i "287s/.*/fScoringVolume = logicPb_Air;\/\/铅层外的剂量/g" src/DetectorConstruction.cc

for ((ii=1;ii<5;ii++)); do
    value=$((ii * 5))  # 计算值
    sed -i "20s/.*/constexpr G4double Pb_Thickness=$value*mm;\/\/Pb厚度/g" include/constants.hh

    cd build 
    make
    ./exampleB1 -m run2.mac
    cd -
done

# 恢复原始文件
mv src/DetectorConstruction.cc.bak src/DetectorConstruction.cc
mv include/constants.hh.bak include/constants.hh
