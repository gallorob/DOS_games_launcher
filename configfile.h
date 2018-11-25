#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QString>
#include <QStringList>

class ConfigFile
{
public:
    ConfigFile();
    QString getFileConfiguration();
    void dumpToFile(QString filename); // todo: implement

    // variables for config file (default values)

    // sdl
    bool fullscreen = false;
    bool fulldouble = false;
    QString fullresolution = "original";
    QString windowresolution = "original";
    QString output = "surface";
    bool autolock = true;
    uint sensitivity = 100;
    bool waitonerror = true;
    QStringList priority = {"higher","normal"};
    QString mapperfile = "mapper-0.74.map";
    bool usescancodes = true;
    // dosbox
    QString language = "";
    QString machine = "svga_s3";
    QString captures = "captures";
    uint memsize = 512;
    // render
    uint frameskip = 0;
    bool aspect = false;
    QString scaler = "normal2x";
    // cpu
    QString core = "auto";
    QString cputype = "auto";
    QString cycles = "auto";
    uint fixed_cycles = 3000; // write to file only if 'cycles' is 'fixed'
    uint cycleup = 100;
    uint cycledown = 20;
    // mixer
    bool nosound = false;
    uint rate = 44100;
    uint blocksize = 2048;
    uint prebuffer = 10;
    // midi
    QString mpu401 = "intelligent";
    QString mididevice = "default";
    QString midiconfig = "";
    // sblaster
    QString sbtype = "sb16";
    uint sbbase = 220;
    uint irq = 7;
    uint dma = 1;
    uint hdma = 5;
    bool sbmixer = true;
    QString oplmode = "auto";
    QString oplemu = "default";
    uint oplrate = 44100;
    // gus
    bool gus = false;
    uint gusrate = 44100;
    uint gusbase = 240;
    uint gusirq = 5;
    uint gusdma = 3;
    QString ultradir = "C:\\ULTRASND";
    // speaker
    bool pcspeaker = true;
    uint pcrate = 44100;
    QString tandy = "auto";
    uint tandyrate = 44100;
    bool disney = true;
    // joystick
    QString joysticktype = "auto";
    bool timed = true;
    bool autofire = false;
    bool swap34 = false;
    bool buttonwrap = false;
    // serial
    QString serial1 = "dummy";
    QString serial2 = "dummy";
    QString serial3 = "disabled";
    QString serial4 = "disabled";
    // dos
    bool xms = true;
    bool ems = true;
    bool umb = true;
    QString keyboardlayout = "auto";
    // ipx
    bool ipx = false;
    // autoexec
    QString autoexec = "cls";
};

#endif // CONFIGFILE_H
