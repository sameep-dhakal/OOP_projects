
#include "PossibleChar.h"

PossibleChar::PossibleChar(
    
    std::vector<cv::Point> _contour) {
    contour = _contour;

    boundGarneRect = cv::boundingRect(contour);

    intCenterX = (boundGarneRect.x + boundGarneRect.x + boundGarneRect.width) / 2;
    intCenterY = (boundGarneRect.y + boundGarneRect.y + boundGarneRect.height) / 2;

    dblDiagonalSize = sqrt(pow(boundGarneRect.width, 2) + pow(boundGarneRect.height, 2));

    dblAspectRatio = (float)boundGarneRect.width / (float)boundGarneRect.height;
}
