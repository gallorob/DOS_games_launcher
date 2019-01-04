#include <QFile>
#include "configfile.h"

ConfigFile::ConfigFile() {
}

QString ConfigFile::getFileConfiguration() {
    return QString::fromLocal8Bit("[sdl]")+
            ("\nfullscreen=")+(this->fullscreen ? "true" : "false")+
            ("\nfulldouble=")+(this->fulldouble ? "true" : "false")+
            ("\nfullresolution=")+this->fullresolution+
            ("\nwindowresolution=")+this->windowresolution+
            ("\noutput=")+this->output+
            ("\nautolock=")+(this->autolock ? "true" : "false")+
            ("\nsensitivity=")+QString::number(this->sensitivity)+
            ("\nwaitonerror=")+(this->waitonerror ? "true" : "false")+
            ("\npriority=")+this->priority[0]+(",")+this->priority[1]+
            ("\nmapperfile=")+this->mapperfile+
            ("\nusescancodes=")+(this->usescancodes ? "true" : "false")+
            ("\n[dosbox]")+
            ("\nlanguage=")+this->language+
            ("\nmachine=")+this->machine+
            ("\ncaptures=")+this->captures+
            ("\nmemsize=")+QString::number(this->memsize)+
            ("\n[render]")+
            ("\nframeskip=")+QString::number(this->frameskip)+
            ("\naspect=")+(this->aspect ? "true" : "false")+
            ("\nscaler=")+this->scaler+
            ("\n[cpu]")+
            ("\ncore=")+this->core+
            ("\ncputype=")+this->cputype+
            ("\ncycles=")+(this->cycles.compare(QString("fixed")) == 0 ? QString::number(this->fixed_cycles) : this->cycles)+
            ("\ncycleup=")+QString::number(this->cycleup)+
            ("\ncycledown=")+QString::number(this->cycledown)+
            ("\n[mixer]")+
            ("\nnosound=")+(this->nosound ? "true" : "false")+
            ("\nrate=")+QString::number(this->rate)+
            ("\nblocksize=")+QString::number(this->blocksize)+
            ("\nprebuffer=")+QString::number(this->prebuffer)+
            ("\n[midi]")+
            ("\nmpu401=")+this->mpu401+
            ("\nmididevice=")+this->mididevice+
            ("\nmidiconfig=")+this->midiconfig+
            ("\n[sblaster]")+
            ("\nsbtype=")+this->sbtype+
            ("\nsbbase=")+QString::number(this->sbbase)+
            ("\nirq=")+QString::number(this->irq)+
            ("\ndma=")+QString::number(this->dma)+
            ("\nhdma=")+QString::number(this->hdma)+
            ("\nsbmixer=")+(this->sbmixer ? "true" : "false")+
            ("\noplmode=")+this->oplmode+
            ("\noplemu=")+this->oplemu+
            ("\noplrate=")+QString::number(this->oplrate)+
            ("\n[gus]")+
            ("\ngus=")+(this->gus ? "true" : "false")+
            ("\ngusrate=")+QString::number(this->gusrate)+
            ("\ngusbase=")+QString::number(this->gusbase)+
            ("\ngusirq=")+QString::number(this->gusirq)+
            ("\ngusdma=")+QString::number(this->gusdma)+
            ("\nultradir=")+this->ultradir+
            ("\n[speaker]")+
            ("\npcspeaker=")+(this->pcspeaker ? "true" : "false")+
            ("\npcrate=")+QString::number(this->pcrate)+
            ("\ntandy=")+this->tandy+
            ("\ntandyrate=")+QString::number(this->tandyrate)+
            ("\ndisney=")+(this->disney ? "true" : "false")+
            ("\n[joystick]")+
            ("\njoysticktype=")+this->joysticktype+
            ("\ntimed=")+(this->timed ? "true" : "false")+
            ("\nautofire=")+(this->autofire ? "true" : "false")+
            ("\nswap34=")+(this->swap34 ? "true" : "false")+
            ("\nbuttonwrap=")+(this->buttonwrap ? "true" : "false")+
            ("\n[serial]")+
            ("\nserial1=")+this->serial1+
            ("\nserial2=")+this->serial2+
            ("\nserial3=")+this->serial3+
            ("\nserial4=")+this->serial4+
            ("\n[dos]")+
            ("\nxms=")+(this->xms ? "true" : "false")+
            ("\nems=")+(this->ems ? "true" : "false")+
            ("\numb=")+(this->umb ? "true" : "false")+
            ("\nkeyboardlayout=")+this->keyboardlayout+
            ("\n[ipx]")+
            ("\nipx=")+(this->ipx ? "true" : "false")+
            ("\n[autoexec]\n")+
            this->autoexec;
}

void ConfigFile::dumpToFile(QString filename) {
    QFile outputFile(filename);
    if(outputFile.open(QIODevice::WriteOnly)) {
        outputFile.write(this->getFileConfiguration().toStdString().c_str());
    }
    outputFile.close();
}
