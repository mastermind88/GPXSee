#ifndef ONLINEMAP_H
#define ONLINEMAP_H

#include "common/range.h"
#include "common/rectc.h"
#include "map.h"
#include "tileloader.h"

class OnlineMap : public Map
{
	Q_OBJECT

public:
	OnlineMap(const QString &fileName, const QString &name, const QString &url,
	  const Range &zooms, const RectC &bounds, qreal tileRatio,
	  const QList<HTTPHeader> &headers, int tileSize, bool scalable,
	  bool invertY, bool quadTiles, QObject *parent = 0);

	QString name() const {return _name;}

	QRectF bounds();
	RectC llBounds(const Projection &) {return _bounds;}
	qreal resolution(const QRectF &rect);

	int zoom() const {return _zoom;}
	void setZoom(int zoom) {_zoom = zoom;}
	int zoomFit(const QSize &size, const RectC &rect);
	int zoomIn();
	int zoomOut();

	QPointF ll2xy(const Coordinates &c);
	Coordinates xy2ll(const QPointF &p);

	void draw(QPainter *painter, const QRectF &rect, Flags flags);

	void load(const Projection &in, const Projection &out, qreal deviceRatio,
	  bool hidpi);
	void clearCache() {_tileLoader->clearCache();}

private:
	int limitZoom(int zoom) const;
	qreal tileSize() const;
	qreal coordinatesRatio() const;
	qreal imageRatio() const;

	TileLoader *_tileLoader;
	QString _name;
	Range _zooms;
	RectC _bounds;
	int _zoom;
	int _tileSize;
	qreal _mapRatio, _tileRatio;
	bool _scalable;
	bool _invertY;
};

#endif // ONLINEMAP_H
