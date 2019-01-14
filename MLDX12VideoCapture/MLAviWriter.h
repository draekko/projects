#pragma once

#include <string>
#include <stdint.h>
#include <vector>
#include <stdio.h>

class MLAviWriter {
public:
    MLAviWriter(void);
    ~MLAviWriter(void);

    enum ImageFormat {
        IF_YUV422v210,
    };

    bool Init(std::wstring path, int width, int height, int fps, ImageFormat imgFmt);

    void AddImage(const uint32_t * img, int bytes);

    void Term(void);

    bool IsOpen(void) const { return mFp != nullptr; }

private:

    int mWidth;
    int mHeight;
    int mFps;
    int mImgFmt;

    struct RiffChunk {
        uint64_t pos;
        uint64_t size;
        bool bDone;
    };

    struct ListChunk {
        uint64_t pos;
        uint64_t size;
        bool bDone;
    };

    std::vector<RiffChunk> mRiffChunks;
    std::vector<ListChunk> mListChunks;

    int mLastRiffIdx;
    int mLastMoviIdx;

    int mTotalFrames;

    uint64_t mAviMainHeaderPos;
    uint64_t mAviStreamHeaderPos;

    int WriteRiff(const char *fccS);
    void FinishRiff(int idx);

    int WriteList(const char *fccS);
    void FinishList(int idx);

    void WriteAviMainHeader(void);
    void WriteAviStreamHeader(void);
    void WriteBitmapInfoHeader(void);

    void WriteFccHeader(const char *fcc, int bytes);

    void WriteStreamDataHeader(uint32_t fcc, int bytes);

    uint32_t ImageBytes(void) const;

    void RestartRiff(void);

    FILE *mFp;
};
