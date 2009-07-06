// EngineControl.h
// Created 7/5/2009 by RJ Ryan (rryan@mit.edu)

#ifndef ENGINECONTROL_H
#define ENGINECONTROL_H

#include <QObject>

#include "configobject.h"

/**
 * EngineControl is an abstract base class for objects which implement
 * functionality pertaining to EngineBuffer. An EngineControl is meant to be a
 * succinct implementation of a given EngineBuffer feature. Previously,
 * EngineBuffer was an example of feature creep -- this is the result.
 *
 * When writing an EngineControl class, the following two properties hold:
 *
 * EngineControl::process will only be called during an EngineBuffer::process
 * callback from the sound engine. This implies that any ControlObject accesses
 * made in either of these methods are mutually exclusive, since one is
 * exclusively in the call graph of the other.
 * 
 * Furthermore, most slots that are connected to Mixxx ControlObjects are safe
 * to process without locking EngineBuffer/EngineControl owned values, since
 * Mixxx only synchronizes ControlObjects in the SoundManager callback, and thus
 * EngineBuffer::process (and correspondingly, EngineControl::process) are
 * mutually exclusive to any ControlObject related slots that fire on an
 * EngineControl. This is not true in every case, so when in doubt, ask a core
 * developer.
 */
class EngineControl : public QObject {
    Q_OBJECT
    
    public:

    EngineControl(const char * _group, const ConfigObject<ConfigValue> * _config);
    virtual ~EngineControl();
    
    virtual double process(const double currentSample, const double totalSamples) {
        return 0;
    }
    
    void setCurrentSample(const double currentSample) {
        m_dCurrentSample = currentSample;
    }
    double getCurrentSample() {
        return m_dCurrentSample;
    }

private:
    const char* getGroup() {
        return m_pGroup;
    }

    const ConfigObject<ConfigValue>* getConfig() {
        return m_pConfig;
    }
    
    const char* m_pGroup;
    const ConfigObject<ConfigValue>* m_pConfig;
    double m_dCurrentSample;
};


#endif /* ENGINECONTROL_H */
