// Copyright 2016 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include <QDialogButtonBox>
#include <QTabWidget>
#include <QVBoxLayout>

#include "DolphinQt2/Config/ARCodeWidget.h"
#include "DolphinQt2/Config/FilesystemWidget.h"
#include "DolphinQt2/Config/GameConfigWidget.h"
#include "DolphinQt2/Config/GeckoCodeWidget.h"
#include "DolphinQt2/Config/InfoWidget.h"
#include "DolphinQt2/Config/PatchesWidget.h"
#include "DolphinQt2/Config/PropertiesDialog.h"
#include "UICommon/GameFile.h"

PropertiesDialog::PropertiesDialog(QWidget* parent, const UICommon::GameFile& game)
    : QDialog(parent)
{
  setWindowTitle(QStringLiteral("%1: %2 - %3")
                     .arg(QString::fromStdString(game.GetFileName()),
                          QString::fromStdString(game.GetGameID()),
                          QString::fromStdString(game.GetLongName())));
  QVBoxLayout* layout = new QVBoxLayout();

  QTabWidget* tab_widget = new QTabWidget(this);
  InfoWidget* info = new InfoWidget(game);

  ARCodeWidget* ar = new ARCodeWidget(game);
  GeckoCodeWidget* gecko = new GeckoCodeWidget(game);
  PatchesWidget* patches = new PatchesWidget(game);
  GameConfigWidget* game_config = new GameConfigWidget(game);

  connect(gecko, &GeckoCodeWidget::OpenGeneralSettings, this,
          &PropertiesDialog::OpenGeneralSettings);

  connect(ar, &ARCodeWidget::OpenGeneralSettings, this, &PropertiesDialog::OpenGeneralSettings);

  tab_widget->addTab(game_config, tr("Game Config"));
  tab_widget->addTab(patches, tr("Patches"));
  tab_widget->addTab(ar, tr("AR Codes"));
  tab_widget->addTab(gecko, tr("Gecko Codes"));
  tab_widget->addTab(info, tr("Info"));

  if (DiscIO::IsDisc(game.GetPlatform()))
  {
    FilesystemWidget* filesystem = new FilesystemWidget(game);
    tab_widget->addTab(filesystem, tr("Filesystem"));
  }

  layout->addWidget(tab_widget);

  QDialogButtonBox* ok_box = new QDialogButtonBox(QDialogButtonBox::Ok);
  connect(ok_box, &QDialogButtonBox::accepted, this, &PropertiesDialog::accept);
  layout->addWidget(ok_box);

  setLayout(layout);
}
