#include "sculptor.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdlib.h>

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    // aloca a matriz de voxels v
    // construtor

    v = new Voxel **[nx];

    for(int i = 0; i < nx; i++ ){

        v[i] = new Voxel *[ny];

        for(int j = 0; j < ny; j++){

            v[i][j] = new Voxel [nz];

        }
    }

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){

                v[i][j][k].show = false;
                v[i][j][k].r = 0;
                v[i][j][k].g = 0;
                v[i][j][k].b = 0;
            }
        }
    }
}

Sculptor::~Sculptor(){
//destrutor

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            delete[] v[i][j];
        }
    }
}

void Sculptor::setColor(float r, float g, float b, float a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Sculptor::putVoxel(int x, int y, int z){
    this->v[x][y][z].show = true;
    this->v[x][y][z].r = this->r;
    this->v[x][y][z].g = this->g;
    this->v[x][y][z].b = this->b;
    this->v[x][y][z].a = this->a;
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i < x1; i++){
        for (int j = y0; j < y1; j++){
            for (int k = z0; k < z1; k++){
                putVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i < x1; i++){
        for (int j = y0; j < y1; j++){
            for (int k = z0; k < z1; k++){
                cutVoxel(i, j, k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (((pow((i - xcenter), 2) / (pow(radius, 2))) +
                     (pow((j - ycenter), 2) / (pow(radius, 2))) +
                     (pow((k - zcenter), 2) / (pow(radius, 2)))) <= 1) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (((pow((i - xcenter), 2) / (pow(radius, 2))) +
                     (pow((j - ycenter), 2) / (pow(radius, 2))) +
                     (pow((k - zcenter), 2) / (pow(radius, 2)))) <= 1) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (((pow((i - xcenter), 2) / (pow(rx, 2))) +
                     (pow((j - ycenter), 2) / (pow(ry, 2))) +
                     (pow((k - zcenter), 2) / (pow(rz, 2)))) <= 1) {
                    putVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (((pow((i - xcenter), 2) / (pow(rx, 2))) +
                     (pow((j - ycenter), 2) / (pow(ry, 2))) +
                     (pow((k - zcenter), 2) / (pow(rz, 2)))) <= 1) {
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename){
    std::ofstream fout;

    int vOn = 0;
    int nvertices, nfaces;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show == true) {
                    vOn++;
                }
            }
        }
    }
    std::ofstream arquivo_off;
    arquivo_off.open(filename);

    if (!arquivo_off.is_open()) {
        std::cout << "Erro ao abrir o arquivo " << std::endl;
    }

    arquivo_off << "OFF" << std::endl;
    // conta quantos voxels estao marcados com show == true
    // lasso aninhado

    arquivo_off << (vOn * 8) << " " << (vOn * 6) << " " << 0 << " " << std::endl;

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show == true) {
                    arquivo_off
                        << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl
                        << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl
                        << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl
                        << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl
                        << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl
                        << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl
                        << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl
                        << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    int contadorFace = 0;

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show == true) {
                    arquivo_off << "4"
                                << " " << contadorFace + 0 << " " << contadorFace + 3
                                << " " << contadorFace + 2 << " " << contadorFace + 1
                                << " " << std::fixed << std::setprecision(1)
                                << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                                << "4"
                                << " " << contadorFace + 4 << " " << contadorFace + 5
                                << " " << contadorFace + 6 << " " << contadorFace + 7
                                << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                                << "4"
                                << " " << contadorFace + 0 << " " << contadorFace + 1
                                << " " << contadorFace + 5 << " " << contadorFace + 4
                                << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                                << "4"
                                << " " << contadorFace + 0 << " " << contadorFace + 4
                                << " " << contadorFace + 7 << " " << contadorFace + 3
                                << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                                << "4"
                                << " " << contadorFace + 7 << " " << contadorFace + 6
                                << " " << contadorFace + 2 << " " << contadorFace + 3
                                << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << "\n"
                                << "4"
                                << " " << contadorFace + 1 << " " << contadorFace + 2
                                << " " << contadorFace + 6 << " " << contadorFace + 5
                                << " " << v[i][j][k].r << " " << v[i][j][k].g << " "
                                << v[i][j][k].b << " " << v[i][j][k].a << std::endl;

                    contadorFace = contadorFace + 8;
                }
            }
        }
    }

    arquivo_off.close();

}


