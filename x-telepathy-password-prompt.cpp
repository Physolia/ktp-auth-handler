/*
 * Copyright (C) 2011 David Edmundson <kde@davidedmundson.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "x-telepathy-password-prompt.h"
#include "ui_x-telepathy-password-prompt.h"

#include <KTp/wallet-interface.h>

#include <KIcon>
#include <KDebug>

XTelepathyPasswordPrompt::XTelepathyPasswordPrompt(const Tp::AccountPtr &account, QWidget *parent)
    : KDialog(parent),
      ui(new Ui::XTelepathyPasswordPrompt)
{
    ui->setupUi(mainWidget());

    setWindowIcon(KIcon(QLatin1String("telepathy-kde")));

    ui->accountName->setText(account->displayName());
    ui->accountIcon->setPixmap(KIcon(QLatin1String("dialog-password")).pixmap(60, 60));
    ui->title->setPixmap(KIcon(account->iconName()).pixmap(22, 22));

    KTp::WalletInterface wallet(this->effectiveWinId());

    if (wallet.isOpen()) {
        ui->savePassword->setChecked(true);
        if (wallet.hasPassword(account)) {
            ui->passwordLineEdit->setText(wallet.password(account));
        }
    } else {
        ui->savePassword->setDisabled(true);
    }
}

XTelepathyPasswordPrompt::~XTelepathyPasswordPrompt()
{
    delete ui;
}

QString XTelepathyPasswordPrompt::password() const
{
    return ui->passwordLineEdit->text();
}

bool XTelepathyPasswordPrompt::savePassword() const
{
    return ui->savePassword->isChecked();
}

#include "x-telepathy-password-prompt.moc"
