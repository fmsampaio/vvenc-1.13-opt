from AsyncManager import AsyncManager

BASE_FOLDER = '/home/research-data/rodrigo/vvenc-search'

VVENC_CMD = f'{BASE_FOLDER}/vvenc-1.13-opt/bin/release-static/vvencFFapp'
VTM_CMD_DECODER = f'{BASE_FOLDER}/vtm-decoder/DecoderAppStatic'
ENCODER_CFG = f'{BASE_FOLDER}/vvenc-1.13-opt/cfg'

YUV_VIDEOS_FOLDER = f'/home/research-data/video-sequences'
CFG_VIDEOS_FOLDER = f'{BASE_FOLDER}/vvenc-1.13-opt/cfg/per-sequence'

OUTPUTS_FOLDER = f'{BASE_FOLDER}/outputs'

VTM_OUTPUTS_FOLDER = f'{OUTPUTS_FOLDER}/vtm-reports'

ENCODED_OUTPUTS_FOLDER = f'{OUTPUTS_FOLDER}/encoded'

DECODED_OUTPUTS_FOLDER = f'{OUTPUTS_FOLDER}/decoded'

TRACEFILES_OUTPUTS_FOLDER = f'{OUTPUTS_FOLDER}/tracefiles'

VIDEOS = [
    ('BQSquare', 'BQSquare_416x240_60.yuv'),
    ('Tango2','Tango2_3840x2160_60fps_10bit_420.yuv'),
    ('FoodMarket4','FoodMarket4_3840x2160_60fps_10bit_420.yuv'),
    ('Campfire','Campfire_3840x2160_30fps_bt709_420_videoRange.yuv'),
    ('CatRobot','CatRobot_3840x2160_60fps_10bit_420_jvet.yuv'), 
    ('DaylightRoad2','DaylightRoad2_3840x2160_60fps_10bit_420.yuv'),
    ('ParkRunning3','ParkRunning3_3840x2160_50fps_10bit_420.yuv'),
    ('MarketPlace','MarketPlace_1920x1080_60fps_10bit_420.yuv'),
    ('RitualDance','RitualDance_1920x1080_60fps_10bit_420.yuv'),
    ('BasketballDrive','BasketballDrive_1920x1080_50.yuv'),
    ('Cactus','Cactus_1920x1080_50.yuv'),
    ('BQTerrace','BQTerrace_1920x1080_60.yuv'),
    ('RaceHorsesC','RaceHorsesC_832x480_30.yuv'),
    ('BQMall','BQMall_832x480_60.yuv'),
    ('PartyScene','PartyScene_832x480_50.yuv'),
    ('BasketballDrill','BasketballDrill_832x480_50.yuv'),
]

FRAMES_TO_BE_CODED = 97
QPs = [22,27,32,37]

CONFIGS = [
    ('faster', 'randomaccess_faster.cfg'),
    ('fast', 'randomaccess_fast.cfg'),
    ('medium', 'randomaccess_medium.cfg'),
    ('slow', 'randomaccess_slow.cfg'),
    ('slower', 'randomaccess_slower.cfg')
]

if __name__ == '__main__':

    manager = AsyncManager(maxProcessParallel=10)

    for video in VIDEOS:
        for qp in QPs:
            for config in CONFIGS:
                experimentKey = f'{video[0]}_{qp}_{config[0]}'

                vtmCommand = f'{VTM_CMD_DECODER} -b {ENCODED_OUTPUTS_FOLDER}/{experimentKey}.bin --TraceFile={TRACEFILES_OUTPUTS_FOLDER}/{experimentKey}.csv --TraceRule=D_BLOCK_STATISTICS_CODED:poc>=0'
                vtmReportFile = f'{VTM_OUTPUTS_FOLDER}/{experimentKey}.report'

                manager.addExecution(
                    key = experimentKey,
                    command = vtmCommand,
                    outputFileName = vtmReportFile
                )

    manager.start()