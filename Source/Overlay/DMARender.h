#pragma once
#include <string>
#include <d3d11.h>

namespace DMARender {
    struct MapTransform {
        float dragOffsetX;
        float dragOffsetY;
        float mapZoom;
        float mapWidth;
        float mapHeight;
        MapTransform() {
            this->dragOffsetX = 0;
            this->dragOffsetY = 0;
            this->mapZoom = -1;
            this->mapWidth = 0;
            this->mapHeight = 0;
        }
    };

    
}