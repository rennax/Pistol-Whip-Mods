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
            sec.debris = DebrisNative(s.debris); 


            //Fuck me there gotta be a better way of doing this.. 
            switch ((Section)s.section)
            {
                case Section.Filled:

                    break;
                case Section.Empty:
                    Models.EmptySection es = (Models.EmptySection)s;
                    EmptySection emptySection = (EmptySection)sec;
                    emptySection.laneWidth = es.laneWidth;
                    emptySection.solidLane = es.solidLane;
                    break;
                case Section.Ground:
                    Models.GroundSection gs = (Models.GroundSection)s;
                    GroundSection groundSection = (GroundSection)sec;
                    groundSection.laneWidth = gs.laneWidth;
                    groundSection.solidLane = gs.solidLane;
                    groundSection.decorationDistance = gs.decorationDistance;
                    groundSection._groundDecorator = (EGroundDecorator)gs._groundDecorator;
                    break;
                case Section.Alley:
                    Models.AlleySection als = (Models.AlleySection)s;
                    AlleySection alleySection = (AlleySection)sec;
                    alleySection.laneMinWidth = als.laneMinWidth;
                    alleySection.laneMaxWidth = als.laneMaxWidth;
                    alleySection.buildingFloorHeight = als.buildingFloorHeight;
                    alleySection.buildingMinFloors = als.buildingMinFloors;
                    alleySection.buildingMaxFloors = als.buildingMaxFloors;
                    alleySection.buildingMinLength = als.buildingMinLength;
                    alleySection.buildingMaxLength = als.buildingMaxLength;
                    alleySection.minorCrossMin = als.minorCrossMin;
                    alleySection.minorCrossMax = als.minorCrossMax;
                    alleySection.majorCrossInterval = als.majorCrossInterval;
                    alleySection.majorCrossMin = als.majorCrossMin;
                    alleySection.majorCrossMax = als.majorCrossMax;
                    alleySection.symmetrical = als.symmetrical;
                    alleySection._wallDecorator = (EWallDecorator)als._wallDecorator;
                    alleySection._groundDecorator = (EGroundDecorator)als._groundDecorator;
                    alleySection._alleyDecorator = (EGroundDecorator)als._alleyDecorator;
                    alleySection.alleyDecorationDepth = als.alleyDecorationDepth;
                    break;
                case Section.Rooms:
                    Models.RoomSection rs = (Models.RoomSection)s;
                    RoomSection roomSection = (RoomSection)sec;
                    roomSection.roomWidthMin = rs.roomWidthMin;
                    roomSection.roomWidthMax = rs.roomWidthMax;
                    roomSection.roomLengthMin = rs.roomLengthMin;
                    roomSection.roomLengthMax = rs.roomLengthMax;
                    roomSection.roomHeightMin = rs.roomHeightMin;
                    roomSection.roomHeightMax = rs.roomHeightMax;
                    roomSection.roomShuffleMax = rs.roomShuffleMax;
                    roomSection.spacerMinLength = rs.spacerMinLength;
                    roomSection.spacerMaxLength = rs.spacerMaxLength;
                    roomSection.spacerMinWidth = rs.spacerMinWidth;
                    roomSection.spacerMaxWidth = rs.spacerMaxWidth;
                    roomSection.spacerMinHeight = rs.spacerMinHeight;
                    roomSection.spacerMaxHeight = rs.spacerMaxHeight;
                    roomSection.propBorderWidth = rs.propBorderWidth;

                    roomSection._wallDecorator = (EWallDecorator)rs._wallDecorator;
                    roomSection._edgeDecorator = (EGroundDecorator)rs._edgeDecorator;
                    roomSection._groundDecorator = (EGroundDecorator)rs._groundDecorator;
                    break;
                case Section.Hallways:
                    Models.HallwaySection hs = (Models.HallwaySection)s;
                    HallwaySection hallwaySection = (HallwaySection)sec;
                    hallwaySection.centerWidthMin = hs.centerWidthMin;
                    hallwaySection.centerWidthMax = hs.centerWidthMax;
                    hallwaySection.centerHeightMin = hs.centerHeightMin;
                    hallwaySection.centerHeightMax = hs.centerHeightMax;
                    hallwaySection.crossWidthMin = hs.crossWidthMin;
                    hallwaySection.crossWidthMax = hs.crossWidthMax;
                    hallwaySection.crossIntervalMin = hs.crossIntervalMin;
                    hallwaySection.crossIntervalMax = hs.crossIntervalMax;
                    hallwaySection.crossHeightMin = hs.crossHeightMin;
                    hallwaySection.crossHeightMax = hs.crossHeightMax;
                    hallwaySection.crossDepthMin = hs.crossDepthMin;
                    hallwaySection.crossDepthMax = hs.crossDepthMax;
                    hallwaySection.symmetrical = hs.symmetrical;

                    break;
                case Section.Offices:
                    Models.OfficeSection os = (Models.OfficeSection)s;
                    OfficeSection officeSection = (OfficeSection)sec;
                    officeSection.centerWidthMin = os.centerWidthMin;
                    officeSection.centerWidthMax = os.centerWidthMax;
                    officeSection.centerHeightMin = os.centerHeightMin;
                    officeSection.centerHeightMax = os.centerHeightMax;
                    officeSection.officeWidthMin = os.officeWidthMin;
                    officeSection.officeWidthMax = os.officeWidthMax;
                    officeSection.officeIntervalMin = os.officeIntervalMin;
                    officeSection.officeIntervalMax = os.officeIntervalMax;
                    officeSection.officeHeightMin = os.officeHeightMin;
                    officeSection.officeHeightMax = os.officeHeightMax;
                    officeSection.officeDepthMin = os.officeDepthMin;
                    officeSection.officeDepthMax = os.officeDepthMax;
                    officeSection.doorMinWidth = os.doorMinWidth;
                    officeSection.doorMaxWidth = os.doorMaxWidth;
                    officeSection.doorMinStart = os.doorMinStart;
                    officeSection.doorMinEnd = os.doorMinEnd;
                    officeSection.doorHeight = os.doorHeight;
                    officeSection.gapsAreHallways = os.gapsAreHallways;
                    officeSection.minHallwayWidth = os.minHallwayWidth;
                    officeSection.hallwayLength = os.hallwayLength;
                    officeSection.symmetrical = os.symmetrical;
                    break;
                case Section.Rooftops:
                    Models.RooftopSection rts = (Models.RooftopSection)s;
                    RooftopSection rooftopSection = (RooftopSection)sec;
                    rooftopSection.laneWidth = rts.laneWidth;
                    rooftopSection.solidLane = rts.solidLane;
                    rooftopSection.buildingMinDistance = rts.buildingMinDistance;
                    rooftopSection.buildingMaxDistance = rts.buildingMaxDistance;
                    rooftopSection.buildingFloorHeight = rts.buildingFloorHeight;
                    rooftopSection.buildingMinFloors = rts.buildingMinFloors;
                    rooftopSection.buildingMaxFloors = rts.buildingMaxFloors;
                    rooftopSection.buildingMinLength = rts.buildingMinLength;
                    rooftopSection.buildingMaxLength = rts.buildingMaxLength;
                    rooftopSection.buildingMinDepth = rts.buildingMinDepth;
                    rooftopSection.buildingMaxDepth = rts.buildingMaxDepth;
                    rooftopSection.minorCrossMin = rts.minorCrossMin;
                    rooftopSection.minorCrossMax = rts.minorCrossMax;
                    rooftopSection.majorCrossInterval = rts.majorCrossInterval;
                    rooftopSection.majorCrossMin = rts.majorCrossMin;
                    rooftopSection.majorCrossMax = rts.majorCrossMax;
                    rooftopSection.symmetrical = rts.symmetrical;
                    rooftopSection._innerWallDecorator = (EWallDecorator)rts._innerWallDecorator;
                    rooftopSection._leadingWallDecorator = (EWallDecorator)rts._leadingWallDecorator;
                    rooftopSection._groundDecorator = (EGroundDecorator)rts._groundDecorator;
                    rooftopSection._alleyDecorator = (EGroundDecorator)rts._alleyDecorator;
                    rooftopSection._rooftopDecorator = (EGroundDecorator)rts._rooftopDecorator;
                    rooftopSection._laneDecorator = (EGroundDecorator)rts._laneDecorator;
                    rooftopSection.alleyDecorationDepth = rts.alleyDecorationDepth;
                    rooftopSection.buildingDecorationDepth = rts.buildingDecorationDepth;
                    rooftopSection.decorateDeepBuildings = rts.decorateDeepBuildings;

                    break;
                case Section.SplitRooftops:
                    Models.SplitRooftopSection srts = (Models.SplitRooftopSection)s;
                    SplitRooftopSection splitRooftopSection = (SplitRooftopSection)sec;

                    splitRooftopSection.laneWidth = srts.laneWidth;
                    splitRooftopSection.solidLane = srts.solidLane;

                    splitRooftopSection.leftDebris = srts.leftDebris;
                    splitRooftopSection.leftDebrisSettings = DebrisNative(srts.leftDebrisSettings);
                    splitRooftopSection.leftGroundHeight = srts.leftGroundHeight;
                    splitRooftopSection.leftBuildingMinDistance = srts.leftBuildingMinDistance;
                    splitRooftopSection.leftBuildingMaxDistance = srts.leftBuildingMaxDistance;
                    splitRooftopSection.leftBuildingFloorHeight = srts.leftBuildingFloorHeight;
                    splitRooftopSection.leftBuildingMinFloors = srts.leftBuildingMinFloors;
                    splitRooftopSection.leftBuildingMaxFloors = srts.leftBuildingMaxFloors;
                    splitRooftopSection.leftBuildingMinLength = srts.leftBuildingMinLength;
                    splitRooftopSection.leftBuildingMaxLength = srts.leftBuildingMaxLength;
                    splitRooftopSection.leftBuildingMinDepth = srts.leftBuildingMinDepth;
                    splitRooftopSection.leftBuildingMaxDepth = srts.leftBuildingMaxDepth;
                    splitRooftopSection.leftMinorCrossMin = srts.leftMinorCrossMin;
                    splitRooftopSection.leftMinorCrossMax = srts.leftMinorCrossMax;
                    splitRooftopSection.leftMajorCrossInterval = srts.leftMajorCrossInterval;
                    splitRooftopSection.leftMajorCrossMin = srts.leftMajorCrossMin;
                    splitRooftopSection.leftMajorCrossMax = srts.leftMajorCrossMax;
                    splitRooftopSection._leftInnerWallDecorator = (EWallDecorator)srts._leftInnerWallDecorator;
                    splitRooftopSection._leftLeadingWallDecorator = (EWallDecorator)srts._leftLeadingWallDecorator;
                    splitRooftopSection._leftGroundDecorator = (EGroundDecorator)srts._leftGroundDecorator;
                    splitRooftopSection._leftAlleyDecorator = (EGroundDecorator)srts._leftAlleyDecorator;
                    splitRooftopSection._leftRooftopDecorator = (EGroundDecorator)srts._leftRooftopDecorator;
                    splitRooftopSection._leftLaneDecorator = (EGroundDecorator)srts._leftLaneDecorator;
                    splitRooftopSection.leftAlleyDecorationDepth = srts.leftAlleyDecorationDepth;
                    splitRooftopSection.leftBuildingDecorationDepth = srts.leftBuildingDecorationDepth;
                    splitRooftopSection.leftDecorateDeepBuildings = srts.leftDecorateDeepBuildings;

                    splitRooftopSection.rightDebris = srts.rightDebris;
                    splitRooftopSection.rightDebrisSettings = DebrisNative(srts.rightDebrisSettings);
                    splitRooftopSection.rightGroundHeight = srts.rightGroundHeight;
                    splitRooftopSection.rightBuildingMinDistance = srts.rightBuildingMinDistance;
                    splitRooftopSection.rightBuildingMaxDistance = srts.rightBuildingMaxDistance;
                    splitRooftopSection.rightBuildingFloorHeight = srts.rightBuildingFloorHeight;
                    splitRooftopSection.rightBuildingMinFloors = srts.rightBuildingMinFloors;
                    splitRooftopSection.rightBuildingMaxFloors = srts.rightBuildingMaxFloors;
                    splitRooftopSection.rightBuildingMinLength = srts.rightBuildingMinLength;
                    splitRooftopSection.rightBuildingMaxLength = srts.rightBuildingMaxLength;
                    splitRooftopSection.rightBuildingMinDepth = srts.rightBuildingMinDepth;
                    splitRooftopSection.rightBuildingMaxDepth = srts.rightBuildingMaxDepth;
                    splitRooftopSection.rightMinorCrossMin = srts.rightMinorCrossMin;
                    splitRooftopSection.rightMinorCrossMax = srts.rightMinorCrossMax;
                    splitRooftopSection.rightMajorCrossInterval = srts.rightMajorCrossInterval;
                    splitRooftopSection.rightMajorCrossMin = srts.rightMajorCrossMin;
                    splitRooftopSection.rightMajorCrossMax = srts.rightMajorCrossMax;
                    splitRooftopSection._rightInnerWallDecorator = (EWallDecorator)srts._rightInnerWallDecorator;
                    splitRooftopSection._rightLeadingWallDecorator = (EWallDecorator)srts._rightLeadingWallDecorator;
                    splitRooftopSection._rightGroundDecorator = (EGroundDecorator)srts._rightGroundDecorator;
                    splitRooftopSection._rightAlleyDecorator = (EGroundDecorator)srts._rightAlleyDecorator;
                    splitRooftopSection._rightRooftopDecorator = (EGroundDecorator)srts._rightRooftopDecorator;
                    splitRooftopSection._rightLaneDecorator = (EGroundDecorator)srts._rightLaneDecorator;
                    splitRooftopSection.rightAlleyDecorationDepth = srts.rightAlleyDecorationDepth;
                    splitRooftopSection.rightBuildingDecorationDepth = srts.rightBuildingDecorationDepth;
                    splitRooftopSection.rightDecorateDeepBuildings = srts.rightDecorateDeepBuildings;

                    break;
                default:
                    break;
            }

            return sec;
        }

        public static Debris DebrisNative(Models.Debris d)
        {
            return new Debris
            {
                distribution = (Debris.Distribution)d.distribution,
                projection = (Debris.Projection)d.projection,
                spread = (Debris.Spread)d.spread,
                density = d.density,
                interval = d.interval,
                uniformity = d.uniformity,
                minSize = d.minSize,
                maxSize = d.maxSize,
                shape = (Debris.Shape)d.shape,
                buildOnAir = d.buildOnAir,
                timing = (Debris.Timing)d.timing
            };
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

            foreach (var d in g.decorationCubes)
            {
                OscillatingObjectData cube = new OscillatingObjectData
                {
                    restPoint = d.restPoint,
                    moveScale = d.moveScale,
                    phase = d.phase
                };
                geo.decoratorCubes.Add(cube);
            }

            //TODO static props
            //TODO dynamic props

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
