#ifndef XMLPARSER_H
#define XMLPARSER_H

#include "wfsconnector_global.h"

class QXmlStreamReader;
class QXmlStreamAttributes;


struct QName {
    QName(QString qName) {
        int splitIndex = qName.indexOf(":");
        if (splitIndex > 0) {
            prefix = qName.left(splitIndex);
        }
        name = qName.mid(splitIndex + 1);
    }

    QString prefix;
    QString name;
};

class WFSCONNECTORSHARED_EXPORT XmlStreamParser
{
public:

    XmlStreamParser();
    XmlStreamParser(QXmlStreamReader *reader);
    XmlStreamParser(QIODevice *device);

    QXmlStreamReader *reader() const;
    void setXmlReader(QXmlStreamReader *reader);
    void addNamespaceMapping(QString prefix, QString ns);

    /**
     * Starts parsing the underlying xml by reading the next/first start element.
     *
     * @param qName the root element's name.
     * @return true if element was found, false if not or the document has ended.
     */
    bool startParsing(QString qName) const;
    bool hasError() const;
    bool atEnd() const;

    QXmlStreamAttributes attributes() const;
    QString readElementText() const;

    /**
     * Moves to the element living on current level, named by qName, and steps in directly by default.
     *
     * @param qName the name of the element to move to.
     * @param stepIn if to step in the element if found.
     * @return true if element was found, false if element was not found.
     */
    bool moveTo(QString qName, bool stepIn=true) const;
    bool isAtBeginningOf(QString qName, bool stepIn=true) const;
    bool isAtEndOf(QString qName) const;


protected:
    QXmlStreamReader *_reader;

private:
    QMap<QString,QString> _namespaces;

    bool isAtElement(QString qName) const;
};

#endif // XMLPARSER_H