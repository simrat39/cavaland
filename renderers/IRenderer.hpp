//
// Created by simrat39 on 12/29/23.
//

#pragma once

class IRenderer {
public:
    virtual void pre_render() = 0;
    virtual void render(double* data) = 0;
};
