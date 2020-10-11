using System.Collections;
using System.Collections.Generic;
using System;

namespace Models
{
    public class Koreography
    {
        public int mSampleRate = 44100;

        public bool mIgnoreLatencyOffset;

        public List<TempoSectionDef> mTempoSections = new List<TempoSectionDef>();

        public List<KoreographyTrackBase> mTracks = new List<KoreographyTrackBase>();

        public string clipName;

    }

    [Serializable]
    public class TempoSectionDef
    {
        public string sectionName;
        public int startSample;
        public double samplesPerBeat;
        public int beatsPerMeasure;
        public bool bStartNewMeasure;
    }

    [Serializable]
    public class KoreographyTrackBase
    {
        public string mEventID;
        public List<KoreographyEvent> mEventList = new List<KoreographyEvent>();
    }

    [Serializable]
    public class KoreographyEvent
    {
        public int mStartSample;
        public string payload = null;
        public int mEndSample;
    }
}