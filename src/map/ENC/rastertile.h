#ifndef ENC_RASTERTILE_H
#define ENC_RASTERTILE_H

#include <QPixmap>
#include "common/range.h"
#include "map/projection.h"
#include "map/transform.h"
#include "map/textpointitem.h"
#include "mapdata.h"
#include "atlasdata.h"

class TextItem;

namespace ENC {

class RasterTile
{
public:
	RasterTile(const Projection &proj, const Transform &transform,
	  const MapData *data, int zoom, const Range &zoomRange, const QRect &rect,
	  qreal ratio) : _proj(proj), _transform(transform), _map(data), _atlas(0),
		_zoom(zoom), _zoomRange(zoomRange), _rect(rect), _ratio(ratio),
	  _pixmap(rect.width() * ratio, rect.height() * ratio), _valid(false) {}
	RasterTile(const Projection &proj, const Transform &transform,
	  AtlasData *data, int zoom, const Range &zoomRange, const QRect &rect,
	  qreal ratio) : _proj(proj), _transform(transform), _map(0), _atlas(data),
	  _zoom(zoom), _zoomRange(zoomRange), _rect(rect), _ratio(ratio),
	  _pixmap(rect.width() * ratio, rect.height() * ratio), _valid(false) {}

	int zoom() const {return _zoom;}
	QPoint xy() const {return _rect.topLeft();}
	const QPixmap &pixmap() const {return _pixmap;}
	bool isValid() const {return _valid;}

	void render();

private:
	void fetchData(QList<MapData::Poly> &polygons, QList<MapData::Line> &lines,
	  QList<MapData::Point> &points);
	QPointF ll2xy(const Coordinates &c) const
	  {return _transform.proj2img(_proj.ll2xy(c));}
	QPainterPath painterPath(const Polygon &polygon) const;
	QPolygonF polyline(const QVector<Coordinates> &path) const;
	QVector<QPolygonF> polylineM(const QVector<Coordinates> &path) const;
	QPolygonF tsslptArrow(const Coordinates &c, qreal angle) const;
	void processPoints(QList<MapData::Point> &points,
	  QList<TextItem*> &textItems, QList<TextItem *> &lights);
	void processLines(const QList<MapData::Line> &lines,
	  QList<TextItem*> &textItems);
	void processPolygons(const QList<MapData::Poly> &polygons,
	  QList<TextItem*> &textItems);
	void drawBitmapPath(QPainter *painter, const QImage &img,
	  const Polygon &polygon);
	void drawArrows(QPainter *painter, const QList<MapData::Poly> &polygons);
	void drawPolygons(QPainter *painter, const QList<MapData::Poly> &polygons);
	void drawLines(QPainter *painter, const QList<MapData::Line> &lines);
	void drawTextItems(QPainter *painter, const QList<TextItem*> &textItems);

	static bool polyCb(MapData *data, void *context);
	static bool pointCb(MapData *data, void *context);

	Projection _proj;
	Transform _transform;
	const MapData *_map;
	AtlasData *_atlas;
	int _zoom;
	Range _zoomRange;
	QRect _rect;
	qreal _ratio;
	QPixmap _pixmap;
	bool _valid;
};

}

#endif // ENC_RASTERTILE_H
