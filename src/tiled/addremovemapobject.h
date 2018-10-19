/*
 * addremovemapobject.h
 * Copyright 2009, Thorbjørn Lindeijer <thorbjorn@lindeijer.nl>
 *
 * This file is part of Tiled.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QUndoCommand>
#include <QVector>

namespace Tiled {

class MapObject;
class ObjectGroup;

namespace Internal {

class MapDocument;

/**
 * Abstract base class for AddMapObject and RemoveMapObject.
 */
class AddRemoveMapObjects : public QUndoCommand
{
public:
    struct Entry {
        Entry() {}

        Entry(MapObject *mapObject, ObjectGroup *objectGroup)
            : mapObject(mapObject)
            , objectGroup(objectGroup)
        {}

        MapObject *mapObject = nullptr;
        ObjectGroup *objectGroup = nullptr;
        int index = -1;
    };

    AddRemoveMapObjects(MapDocument *mapDocument,
                        const QVector<Entry> &entries,
                        bool ownObjects,
                        QUndoCommand *parent = nullptr);
    ~AddRemoveMapObjects();

    static QVector<Entry> entries(const QList<MapObject *> &objects);
    static QList<MapObject*> objects(const QVector<Entry> &entries);

protected:
    MapDocument *mMapDocument;
    QVector<Entry> mEntries;
    bool mOwnsObjects;
};

/**
 * Undo command that adds an object to a map.
 */
class AddMapObjects : public AddRemoveMapObjects
{
public:
    AddMapObjects(MapDocument *mapDocument,
                  ObjectGroup *objectGroup,
                  MapObject *mapObject,
                  QUndoCommand *parent = nullptr);

    AddMapObjects(MapDocument *mapDocument,
                  const QVector<Entry> &entries,
                  QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;
};

/**
 * Undo command that removes one or more objects from a map.
 */
class RemoveMapObjects : public AddRemoveMapObjects
{
public:
    RemoveMapObjects(MapDocument *mapDocument,
                     MapObject *mapObject,
                     QUndoCommand *parent = nullptr);

    RemoveMapObjects(MapDocument *mapDocument,
                     const QList<MapObject *> &mapObjects,
                     QUndoCommand *parent = nullptr);

    void undo() override;
    void redo() override;
};

} // namespace Internal
} // namespace Tiled
