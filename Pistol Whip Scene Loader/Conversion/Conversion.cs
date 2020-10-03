using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Il2CppSystem;
using SonicBloom.Koreo;
using UnityEngine;
using Il2CppSystem.Collections.Generic;
using MelonLoader;
using UnhollowerBaseLib;

namespace Pistol_Whip_Scene_Loader
{
    public static class ConversionExtension
    {
        public static TrackSection TrackSectionNative(Models.TrackSection s)
        {
            
            TrackSection sec = TrackSection.Create((Section)s.section);
            sec.enemyColor = s.enemy;
            sec.mainColor = s.color;
            sec.fogColor = s.color;
            sec.glowColor = s.glow;
            sec.customColors = s._customColors;
            sec.customEnemyColor = s._customEnemyColor;
            sec.startingWall = s.startingWall;
            sec.endingWall = s.endingWall;
            sec.height = s.height;
            sec.groundHeight = s.groundHeight;
            sec.start = s.start;
            sec.end = s.end;
            sec.min = s.min;
            sec.max = s.max;
            sec.generateDebris = s.generateDebris;
            sec.debris = new Debris
            {
                distribution = (Debris.Distribution)s.debris.distribution,
                projection = (Debris.Projection)s.debris.projection,
                spread = (Debris.Spread)s.debris.spread,
                density = s.debris.density,
                interval = s.debris.interval,
                uniformity = s.debris.uniformity,
                minSize = s.debris.minSize,
                maxSize = s.debris.maxSize,
                shape = (Debris.Shape)s.debris.shape,
                buildOnAir = s.debris.buildOnAir,
                timing = (Debris.Timing)s.debris.timing
            };



            switch ((Section)s.section)
            {
                case Section.Filled:

                    break;
                default:
                    break;
            }

            return sec;
        }

        public static LevelData LevelDataNative(Models.LevelData d)
        {
            LevelData level = new LevelData
            {
                songName = d.songName,
                songLength = d.songLength,
                description = d.description,
                maps = new GameMap[d.gameMaps.Length], // TODO just insert 4, and then disable the diff button for those who are not available?
                sections = new List<TrackSection>(),
                volumes = new List<WorldVolume>(),
                colors = new List<ColorShiftPoint>(),
                worldObjects = new List<WorldObject>(),
                simpleStaticWorldObjects = new List<WorldObject>(),
                simpleDynamicWorldObjects = new List<WorldObject>(),
                staticCullingRanges = new List<CullingRange>(),
                dynamicCullingRanges = new List<CullingRange>(),
                obstacleSet = d.obstacleSet,
                materialPropertiesSet = d.materialPropertiesSet,
                enemySet = d.enemySet
            };
            level.name = $"{d.songName}_Data";

            foreach (var sec in d.sections)
            {
                level.sections.Add(TrackSectionNative(sec));
            }

            for (int i = 0; i < d.gameMaps.Length; i++)
            {
                level.maps[i] = GameMapNative(d.gameMaps[i]);
                level.maps[i].data = level;
                level.maps[i].trackData.level = level;
                level.maps[i].trackData.name = $"{level.songName}_{System.Enum.GetName(typeof(Models.Difficulty), level.maps[i].trackData.difficulty)}"; // "songName_Easy" etc.

            }

            return level;
        }

        public static GameMap GameMapNative(Models.GameMap g)
        {
            TrackData track = TrackDataNative(g.trackData);
            GeoSet geoSet = GeoSetNative(g.geoSet);
            geoSet.track = track;
            GameMap map = new GameMap(geoSet);
            map.isPlayable = g.isPlayable;
            map.enemyIgnoreCount = g.enemyIgnoreCount;
            map.enemyHitIgnoreCount = g.enemyHitIgnoreCount;
            map.enemyCount = g.enemyCount;
            map.rankedEnemyCount = g.rankedEnemyCount;
            map.hitCount = g.hitCount;
            map.rankedHitCount = g.rankedHitCount;
            map.trueMaxScore = g.trueMaxScore;
            map.rankQuotas = new UnhollowerBaseLib.Il2CppStructArray<RankQuota>(0);

            return map;
        }

        public static GeoSet GeoSetNative(Models.GeoSet g)
        {

            GeoSet geo = new GeoSet
            {
                chunkSize = g.chunkSize,
                scale = g.scale,
                chunkData = new List<ChunkMeshData>(),
                chunkSlices = new List<ChunkMeshSlice>(),
                staticProps = new List<WorldObject>(),
                dynamicProps = new List<WorldObject>(),
                decoratorCubes = new List<OscillatingObjectData>()
            };

            foreach (var c in g.chunkData)
            {
                ChunkMeshSlice slice = new ChunkMeshSlice
                {
                    colors = c.colors,
                    meshSizes = c.meshSizes,
                    tris = c.tris,
                    verts = c.verts,
                    z = c.id.z
                };
                geo.chunkSlices.Add(slice);

                ChunkMeshData data = new ChunkMeshData
                {
                    colors = c.colors,
                    meshSizes = c.meshSizes,
                    tris = c.tris,
                    verts = c.verts,
                    id = c.id
                };
                geo.chunkData.Add(data);
            }

            //TODO static props
            //TODO dynamic props
            //TODO decor cubes

            return geo;
        }

        public static TrackData TrackDataNative(Models.TrackData t)
        {
            TrackData track = new TrackData()
            {
                difficulty = (Difficulty)t.difficulty,
                koreography = KoreographyNative(t.koreography),
                playerSpeed = t.playerSpeed,
                sampleRate = t.sampleRate,
                musicMap = new CloudheadGames.PistolWhip.MusicMapperSystem.MusicMap(),
                beatTimes = new List<float>(),
                beats = new List<BeatData>(),
            };

            foreach (var times in t.beatTimes)
            {
                track.beatTimes.Add(times);
            }

            foreach (var b in t.beats)
            {
                BeatData beat = new BeatData(b.time);
                beat.targets.Clear();
                beat.obstacles.Clear();

                foreach (var target in b.targets)
                {
                    beat.targets.Add(TargetDataNative(target));
                }

                foreach (var ob in b.obstacles)
                {
                    ObstacleData obstacle = new ObstacleData
                    {
                        placement = (ObstacleData.Placement)ob.placement,
                        type = (ObstacleData.ObstacleType)ob.type,
                    };
                    beat.obstacles.Add(obstacle);
                }

                track.beats.Add(beat);
            }

            return track;
        }

        public static TargetData TargetDataNative(Models.TargetData t)
        {
            Vector4 rot = t.enemyOffset.rotation;
            TargetData target = new TargetData
            {
                distance = (TargetData.Distance)t.distance,
                placement = t.placement,
                enemyType = t.enemyType,
                enemyOffset = WorldPointNative(t.enemyOffset),
                ignoreForLevelRank = t.ignoreForLevelRank,
                fireTimes = new UnhollowerBaseLib.Il2CppStructArray<float>(t.fireTimes.Count),
                cheevoID = (CheevoID)t.cheevoID,
                noGround = t.noGround
            };

            for (int i = 0; i < t.fireTimes.Count; i++)
            {
                target.fireTimes[i] = t.fireTimes[i];
            }

            target.enemySequence = EnemySequenceNative(t.enemySequence);

            return target;
        }

        public static EnemySequence EnemySequenceNative(Models.EnemySequence es)
        {
            GameObject go = new GameObject();
            EnemySequence enemySequence = go.AddComponent<EnemySequence>();
            enemySequence.actionHolder = new GameObject();
            enemySequence.actionHolder.transform.parent = go.transform;

            enemySequence.forceCheevoID = (CheevoID)es.forceCheevoID;
            enemySequence.actions = new List<EnemyAction>();
            foreach (var action in es.actions)
            {
                EnemyAction acc = EnemyActionNative(action, enemySequence.actionHolder);
                acc.sequence = enemySequence;
                enemySequence.actions.Add(acc);
            }

            return enemySequence;
        }

        public static EnemyAction EnemyActionNative(Models.EnemyAction a, GameObject gameObject)
        {
            EnemyAction action = null;
            MelonLogger.Log(a.GetType().Name);
            switch (a.actionType)
            {
                case 0:
                    MelonLogger.Log("EnemyActionWait");
                    EnemyActionWait actionWait = gameObject.AddComponent<EnemyActionWait>();
                    actionWait.waitTime = ((Models.EnemyActionWait)a).waitTime;
                    action = actionWait;
                    break;
                case 1:
                    MelonLogger.Log("EnemyActionMove");
                    EnemyActionMove actionMove = gameObject.AddComponent<EnemyActionMove>();
                    actionMove.destination = WorldPointNative(((Models.EnemyActionMove)a).destination);
                    actionMove.facing = (EnemyActionMove.Facing)((Models.EnemyActionMove)a).facing;
                    action = actionMove;
                    //((EnemyActionMove)action).speed;
                    break;
                case 2:
                    MelonLogger.Log("EnemyActionAimStart");
                    action = gameObject.AddComponent<EnemyActionAimStart>();
                    break;
                case 3:
                    MelonLogger.Log("EnemyActionAimStop");
                    EnemyActionAimStop actionAimStop = gameObject.AddComponent<EnemyActionAimStop>();
                    actionAimStop.stopFacing = ((Models.EnemyActionAimStop)a).stopFacing;
                    actionAimStop.stopLooking = ((Models.EnemyActionAimStop)a).stopLooking;
                    action = actionAimStop;
                    break;
                case 4:
                    MelonLogger.Log("EnemyActionWait");
                    action = gameObject.AddComponent<EnemyActionFire>();

                    break;
                case 5:
                    MelonLogger.Log("EnemyActionAimAndFire");
                    EnemyActionAimAndFire actionAimAndFire = gameObject.AddComponent<EnemyActionAimAndFire>();
                    actionAimAndFire.stopFacingOnExit = ((Models.EnemyActionAimAndFire)a).stopFacingOnExit;
                    actionAimAndFire.stopLookingOnExit = ((Models.EnemyActionAimAndFire)a).stopLookingOnExit;
                    actionAimAndFire.actionDuration = ((Models.EnemyActionAimAndFire)a).actionDuration;
                    actionAimAndFire.fireTime = ((Models.EnemyActionAimAndFire)a).fireTime;
                    action = actionAimAndFire;
                    break;
                case 15:
                    MelonLogger.Log("EnemyActionStopFiring");
                    action = gameObject.AddComponent<EnemyActionStopFiring>();
                    break;
            }
            action.duration = a.duration;
            action.localStartingPoint = WorldPointNative(a.localStartingPoint);
            action.localEndingPoint = WorldPointNative(a.localEndingPoint);
            action.sequenceStartTime = a.sequenceStartTime;
            return action;
        }

        public static WorldPoint WorldPointNative(Models.WorldPoint w)
        {
            return new WorldPoint
            {
                position = w.position,
                rotation = new Quaternion(w.rotation.x, w.rotation.y, w.rotation.z, w.rotation.w),
            };
        }

        public static Koreography KoreographyNative(Models.Koreography k)
        {

            Koreography koreo = new Koreography();
            koreo.SampleRate = k.mSampleRate;
            koreo.IgnoreLatencyOffset = k.mIgnoreLatencyOffset;

            AudioClip clip = AudioClip.Create(k.clipName, 1, 2, 1, false);
            koreo.SourceClip = clip;

            foreach (var track in k.mTracks)
            {
                KoreographyTrack kTrack = new KoreographyTrack();
                kTrack.EventID = track.mEventID;

                if (track.mEventList == null) continue;
                
                foreach (var e in track.mEventList)
                {
                    KoreographyEvent kEvent = new KoreographyEvent
                    {
                        StartSample = e.mStartSample,
                        EndSample = e.mEndSample,
                        mPayload = null // We dont actually know if any payload is used.. yet
                    };
                    kTrack.AddEvent(kEvent);
                }
                koreo.AddTrack(kTrack);
            }

            List<TempoSectionDef> tempoSections = new List<TempoSectionDef>();
            foreach (var tempo in k.mTempoSections)
            {
                TempoSectionDef tempoSection = new TempoSectionDef
                {
                    SectionName = tempo.sectionName,
                    StartSample = tempo.startSample,
                    SamplesPerBeat = tempo.samplesPerBeat,
                    BeatsPerMeasure = tempo.beatsPerMeasure,
                    DoesStartNewMeasure = tempo.bStartNewMeasure
                };
                tempoSections.Add(tempoSection);
            }

            koreo.OverwriteTempoSections(tempoSections);
            return koreo;
        }
    }
}
