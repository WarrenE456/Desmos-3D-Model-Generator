#pragma once

const char* PRELUDE =
    "d_{ist}=3\n"
    "\\theta_{0}=0\n"
    "\\phi_{0}=1.57\n"
    "p_{roj}\\left(p\\right)=\\left\\{p.z+d_{ist}>0:\\left(\\frac{p.x}{p.z+d_{ist}},\\frac{p.y}{p.z+d_{ist}}\\right)\\right\\}\n"
    "r_{otX}\\left(p,\\theta\\right)=\\left(p.x,p.y\\cos\\theta-p.z\\sin\\theta,p.y\\sin\\theta+p.z\\cos\\theta\\right)\n"
    "r_{otY}\\left(p,\\theta\\right)=\\left(p.x\\cos\\theta+p.z\\sin\\theta,p.y,p.z\\cos\\theta-p.x\\sin\\theta\\right)\n"
    "t\\left(p\\right)=p_{roj}\\left(r_{otX}\\left(r_{otY}\\left(p,-\\phi_{0}\\right),-\\theta_{0}\\right)\\right)\n"
;

