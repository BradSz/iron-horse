#pragma once

namespace iron {
  template<typename Deserialized>
  struct StreamParser
  {
      std::list<Deserialized> operator() (const std::vector<char>& inInput) = 0;
  };

  struct EnvelopedMessageParser
  {
      struct MessageHeader {
          MessageHeader(const std::vector<char>& inInput) : Size(0)
          {
            std::stringstream(std::string(inInput.begin(), inInput.begin() + 4)) >> Size;
          }
          bool isBad() { return Size < 2; }
          int Size;
      };

      struct MessageBody {
          MessageBody(const std::vector<char>& inInput, int size)
            : Value(inInput.begin(), inInput.begin() + size) { }
          std::string Value;
      };

      struct Message {
          MessageHeader Header;
          MessageBody   Body;
      };

      const static int HeaderSize = 10;

      EnvelopedMessageParser() : mRawData(), mHeader() { }

      std::list<Message> operator() (const std::vector<char>& inInput) {
        // Add new data to working space
        mRawData.reserve(mRawData.size() + inInput.size());
        mRawData.insert(mRawData.end(), inInput.begin(), inInput.end());

        std::list<Message> ret;

        int bodySize = mHeader.empty() ? 0 : mHeader->Size;

        bool isHeaderNext  = (mHeader.empty());
        bool isBodyNext    = (!isHeaderNext);
        bool canTryHeader  = isHeaderNext && (mRawData.size() > HeaderSize);
        bool canTryBody    = isBodyNext   && (mRawData.size() > bodySize);
        while (canTryHeader || canTryBody) {
            // Search for next header on failure
            if (canTryHeader) {
                mHeader.reset(new MessageHeader(inInput));
                if (mHeader->isBad()) {
                    mHeader.reset();
                    mRawData.erase(mRawData.begin());
                } else {
                    mRawData.erase(mRawData.begin(), mRawData.begin() + 4);
                }
            }

            // Obtain body for associated header
            if (canTryBody) {
                Message msg;
                msg.Header = *mHeader;
                msg.Body   = MessageBody(mRawData);
                mRawData.erase(mRawData.begin(), mRawData.end() + 4);
                ret.push_back(msg);
            }

            // bookkeeping
            isHeaderNext  = (mHeader.empty());
            isBodyNext    = (!isHeaderNext);
            canTryHeader  = isHeaderNext && (mRawData.size() > HeaderSize);
            canTryBody    = isBodyNext   && (mRawData.size() > bodySize);
        }

        return ret;
      }

    private:
      std::vector<char>              mRawData;
      std::unique_ptr<MessageHeader> mHeader;
  };
} /* iron */
