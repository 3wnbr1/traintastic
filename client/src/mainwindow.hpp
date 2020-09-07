/**
 * client/src/mainwindow.hpp
 *
 * This file is part of the traintastic source code.
 *
 * Copyright (C) 2019-2020 Reinder Feenstra
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef TRAINTASTIC_CLIENT_MAINWINDOW_HPP
#define TRAINTASTIC_CLIENT_MAINWINDOW_HPP

#include <QMainWindow>
#include <QMap>
#include "network/objectptr.hpp"

class MdiArea;
class QSplitter;
class QMdiSubWindow;
class QActionGroup;
class Connection;
class AbstractProperty;
class ObjectEditSubWindow;
class HardwareListSubWindow;
class LuaScriptsSubWindow;
class ServerSettingsSubWindow;
class ServerConsoleWidget;

class MainWindow : public QMainWindow
{
  Q_OBJECT

  protected:
    QSharedPointer<Connection> m_connection;
    ObjectPtr m_world;
    QSplitter* m_splitter;
    MdiArea* m_mdiArea;
    ServerConsoleWidget* m_serverConsole;
    QMap<QString, QMdiSubWindow*> m_mdiSubWindows;
    QAction* m_actionConnectToServer;
    QAction* m_actionDisconnectFromServer;
    QAction* m_actionNewWorld;
    QAction* m_actionLoadWorld;
    QAction* m_actionSaveWorld;
    QAction* m_actionImportWorld;
    QAction* m_actionExportWorld;
    QMenu* m_menuObjects;
    QAction* m_actionLuaScript;
    QAction* m_actionServerSettings;
    QAction* m_actionServerConsole;
    QAction* m_actionTrackPowerOff;
    QAction* m_actionTrackPowerOn;
    QAction* m_actionEmergencyStop;
    QAction* m_actionEdit;
    QByteArray m_beforeFullScreenGeometry;

    void closeEvent(QCloseEvent* event) final;
    void worldChanged();
    void updateWindowTitle();

  protected slots:
    void disconnectFromServer();
    void loadWorld();
    void importWorld();
    void exportWorld();
    void toggleFullScreen();
    void toggleConsole();
    void showAbout();
    void connectionStateChanged();
    void updateActions();
    //void updateModeActions();

  public:
    inline static MainWindow* instance = nullptr;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() final;

    const QSharedPointer<Connection>& connection() { return m_connection; }

  public slots:
    void connectToServer();
    void showObject(const ObjectPtr& object);
    void showObject(const QString& id, const QString& title = "");
};

#endif
