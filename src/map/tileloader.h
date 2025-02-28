#ifndef TILELOADER_H
#define TILELOADER_H

#include <QObject>
#include <QString>
#include "common/downloader.h"
#include "tile.h"

class TileLoader : public QObject
{
	Q_OBJECT

public:
	enum UrlType {
		XYZ,
		QuadTiles,
		BoundingBox
	};

	TileLoader(const QString &dir, QObject *parent = 0);

	void setUrl(const QString &url, UrlType type) {_url = url; _urlType = type;}
	void setHeaders(const QList<HTTPHeader> &headers) {_headers = headers;}
	void setScaledSize(int size);

	void loadTilesAsync(QVector<FetchTile> &list);
	void loadTilesSync(QVector<FetchTile> &list);
	void clearCache();

signals:
	void finished();

private:
	QUrl tileUrl(const FetchTile &tile) const;
	QString tileFile(const FetchTile &tile) const;

	Downloader *_downloader;
	QString _url;
	UrlType _urlType;
	QString _dir;
	QList<HTTPHeader> _headers;
	int _scaledSize;
};

#endif // TILELOADER_H
