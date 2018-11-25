#include <QFile>
#include "configfile.h"

ConfigFile::ConfigFile() {
}

QString ConfigFile::getFileConfiguration() {
    return QString::fromAscii("[sdl]")+
            QString::fromAscii("\nfullscreen=")+(this->fullscreen ? "true" : "false")+
            QString::fromAscii("\nfulldouble=")+(this->fulldouble ? "true" : "false")+
            QString::fromAscii("\nfullresolution=")+this->fullresolution+
            QString::fromAscii("\nwindowresolution=")+this->windowresolution+
            QString::fromAscii("\noutput=")+this->output+
            QString::fromAscii("\nautolock=")+(this->autolock ? "true" : "false")+
            QString::fromAscii("\nsensitivity=")+QString::number(this->sensitivity)+
            QString::fromAscii("\nwaitonerror=")+(this->waitonerror ? "true" : "false")+
            QString::fromAscii("\npriority=")+this->priority[0]+QString::fromAscii(",")+this->priority[1]+
            QString::fromAscii("\nmapperfile=")+this->mapperfile+
            QString::fromAscii("\nusescancodes=")+(this->usescancodes ? "true" : "false")+
            QString::fromAscii("\n[dosbox]")+
            QString::fromAscii("\nlanguage=")+this->language+
            QString::fromAscii("\nmachine=")+this->machine+
            QString::fromAscii("\ncaptures=")+this->captures+
            QString::fromAscii("\nmemsize=")+QString::number(this->memsize)+
            QString::fromAscii("\n[render]")+
            QString::fromAscii("\nframeskip=")+QString::number(this->frameskip)+
            QString::fromAscii("\naspect=")+(this->aspect ? "true" : "false")+
            QString::fromAscii("\nscaler=")+this->scaler+
            QString::fromAscii("\n[cpu]")+
            QString::fromAscii("\ncore=")+this->core+
            QString::fromAscii("\ncputype=")+this->cputype+
            QString::fromAscii("\ncycles=")+this->cycles+
            QString::fromAscii("\ncycleup=")+QString::number(this->cycleup)+
            QString::fromAscii("\ncycledown=")+QString::number(this->cycledown)+
            QString::fromAscii("\n[mixer]")+
            QString::fromAscii("\nnosound=")+(this->nosound ? "true" : "false")+
            QString::fromAscii("\nrate=")+QString::number(this->rate)+
            QString::fromAscii("\nblocksize=")+QString::number(this->blocksize)+
            QString::fromAscii("\nprebuffer=")+QString::number(this->prebuffer)+
            QString::fromAscii("\n[midi]")+
            QString::fromAscii("\nmpu401=")+this->mpu401+
            QString::fromAscii("\nmididevice=")+this->mididevice+
            QString::fromAscii("\nmidiconfig=")+this->midiconfig+
            QString::fromAscii("\n[sblaster]")+
            QString::fromAscii("\nsbtype=")+this->sbtype+
            QString::fromAscii("\nsbbase=")+QString::number(this->sbbase)+
            QString::fromAscii("\nirq=")+QString::number(this->irq)+
            QString::fromAscii("\ndma=")+QString::number(this->dma)+
            QString::fromAscii("\nhdma=")+QString::number(this->hdma)+
            QString::fromAscii("\nsbmixer=")+(this->sbmixer ? "true" : "false")+
            QString::fromAscii("\noplmode=")+this->oplmode+
            QString::fromAscii("\noplemu=")+this->oplemu+
            QString::fromAscii("\noplrate=")+QString::number(this->oplrate)+
            QString::fromAscii("\n[gus]")+
            QString::fromAscii("\ngus=")+(this->gus ? "true" : "false")+
            QString::fromAscii("\ngusrate=")+QString::number(this->gusrate)+
            QString::fromAscii("\ngusbase=")+QString::number(this->gusbase)+
            QString::fromAscii("\ngusirq=")+QString::number(this->gusirq)+
            QString::fromAscii("\ngusdma=")+QString::number(this->gusdma)+
            QString::fromAscii("\nultradir=")+this->ultradir+
            QString::fromAscii("\n[speaker]")+
            QString::fromAscii("\npcspeaker=")+(this->pcspeaker ? "true" : "false")+
            QString::fromAscii("\npcrate=")+QString::number(this->pcrate)+
            QString::fromAscii("\ntandy=")+this->tandy+
            QString::fromAscii("\ntandyrate=")+QString::number(this->tandyrate)+
            QString::fromAscii("\ndisney=")+(this->disney ? "true" : "false")+
            QString::fromAscii("\n[joystick]")+
            QString::fromAscii("\njoysticktype=")+this->joysticktype+
            QString::fromAscii("\ntimed=")+(this->timed ? "true" : "false")+
            QString::fromAscii("\nautofire=")+(this->autofire ? "true" : "false")+
            QString::fromAscii("\nswap34=")+(this->swap34 ? "true" : "false")+
            QString::fromAscii("\nbuttonwrap=")+(this->buttonwrap ? "true" : "false")+
            QString::fromAscii("\n[serial]")+
            QString::fromAscii("\nserial1=")+this->serial1+
            QString::fromAscii("\nserial2=")+this->serial2+
            QString::fromAscii("\nserial3=")+this->serial3+
            QString::fromAscii("\nserial4=")+this->serial4+
            QString::fromAscii("\n[dos]")+
            QString::fromAscii("\nxms=")+(this->xms ? "true" : "false")+
            QString::fromAscii("\nems=")+(this->ems ? "true" : "false")+
            QString::fromAscii("\numb=")+(this->umb ? "true" : "false")+
            QString::fromAscii("\nkeyboardlayout=")+this->keyboardlayout+
            QString::fromAscii("\n[ipx]")+
            QString::fromAscii("ipx=")+(this->ipx ? "true" : "false")+
            QString::fromAscii("\n[autoexec]\n")+
            this->autoexec;
}

void ConfigFile::dumpToFile(QString filename) {
    QFile outputFile(filename);
    if(outputFile.open(QIODevice::WriteOnly)) {
        outputFile.write(this->getFileConfiguration().toStdString().c_str());
    }
    outputFile.close();
}
