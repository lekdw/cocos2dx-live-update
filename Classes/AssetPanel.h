#ifndef	__ASSET_PANEL_H__
#define	__ASSET_PANEL_H__

#include "cocos2d.h"
#include "network/HttpClient.h"


USING_NS_CC;
using namespace network;
using namespace std;

class RefValueMap : public Ref {
public:
	void put(const string &key, Ref *value) {
		map.insert(key, value);
	}

	Ref *get(const string &key) {
		return map.at(key);
	}

	void putInt(const string &key, int value) {
		auto obj = __Integer::create(value);
		put(key, obj);
	}

	int getInt(const string &key) {
		auto obj = (__Integer *)get(key);
		return obj->getValue();
	}

private:
	Map<string, Ref *> map;
};

class AssetPanel : public Node {
public:
	AssetPanel();
	virtual ~AssetPanel();

public:
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();

	CREATE_FUNC(AssetPanel);

private:
	void downloadVersionFile();
	void onDownloadVersionFile(HttpClient *client, HttpResponse *response);

	void downloadNextPackageFile();
	void onProgressDownloadPackageFile(Ref *object);
	void onDownloadPackageFile(HttpClient *client, HttpResponse *response);

	void decompressPackageFile();
	void onProgressDecompressPackageFile(Ref *object);

	bool saveVersionFile(const string &path, const string &buf);
	bool savePackageFile(const string &path, const vector<char> *buf);

private:
	string m_serverVersionFileData;
	int m_clientVersion;
	int m_downloadIndex;
	int m_downloadCount;
	vector<string> m_updatePackages;
};

#endif	// __ASSET_PANEL_H__