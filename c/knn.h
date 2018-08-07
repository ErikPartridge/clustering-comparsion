/**
 * The MIT License
 * Copyright (c) 2017-2018 Erik Partridge
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef KNN_FAST_KNN_H
#define KNN_FAST_KNN_H

#define NUM_POINTS 50000
#define CLUSTERS 6
#define ITERATIONS 1000
#include <math.h>
#define SQRT_MAGIC_F 0x5f3759df 
struct Point {
    float w, x, y, z;
    int centroid;
};

struct Centroid {
    float w, x, y, z;
};


float get_distance(struct Point p, struct Centroid c){
    float dw = (p.w - c.w) * (p.w - c.w);
    float dx = (p.x - c.x) * (p.x - c.x);
    float dy = (p.y - c.y) * (p.y - c.y);
    float dz = (p.z - c.z) * (p.z - c.z);
    return (dw + dx + dy + dz) / 4;
}

char closest_centroid(struct Centroid centroids[], struct Point p){
    char closest = -1;
    float distance = MAXFLOAT;
    for(char i = 0; i < CLUSTERS; i ++){
        float d = get_distance(p, centroids[i]);
        if ( d < distance) {
            closest = i;
            distance = d;
        }
    }
    return closest;
}

void perform_iteration(struct Centroid centroids[], struct Point points[]){
    /*
     * Assign points to the closest centroids
     */
    for(int i = 0; i < NUM_POINTS; i++ ){
        points[i].centroid = closest_centroid(centroids, points[i]);
    }

    char centroid_count[CLUSTERS] = {0};
    float centroid_values[CLUSTERS][4] = {0.0};

    for(int j = 0; j < NUM_POINTS; j++){
        int ctr = points[j].centroid;
        centroid_count[ctr] ++;
        centroid_values[ctr][0] = points[j].w;
        centroid_values[ctr][1] = points[j].x;
        centroid_values[ctr][2] = points[j].y;
        centroid_values[ctr][3] = points[j].z;
    }

    for(char k = 0; k < CLUSTERS; k++){
        centroids[k].w = centroid_values[k][0] / centroid_count[k];
        centroids[k].x = centroid_values[k][1] / centroid_count[k];
        centroids[k].y = centroid_values[k][2] / centroid_count[k];
        centroids[k].z = centroid_values[k][3] / centroid_count[k];
    }

}

void compute_centroids(struct Point points[]) {

    struct Centroid centroids[CLUSTERS];

    for(char j = 0; j < CLUSTERS; j++){
        struct Centroid c = {points[j].w, points[j].x, points[j].y, points[j].z};
        centroids[j] = c;
    }

    for(int k = 0; k < NUM_POINTS; k++){
        points[k].centroid = k % CLUSTERS;
    }

    for(int i = 1; i < ITERATIONS; i ++) {
        perform_iteration(centroids, points);
    }
}

#endif //KNN_FAST_KNN_H
