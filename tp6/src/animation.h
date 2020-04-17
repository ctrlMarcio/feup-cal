#ifndef FICHAJUNG_ANIMATION_H
#define FICHAJUNG_ANIMATION_H

#include <vector>
#include "graphviewer.h"

void
animateLegs(GraphViewer *gv, int node1id, int x1i, int x1f, int y1, int node2id, int x2i, int x2f, int y2,
			int parentNode, int minEdgeid, int minIdAvailable, int msDelay);

#endif //FICHAJUNG_ANIMATION_H
