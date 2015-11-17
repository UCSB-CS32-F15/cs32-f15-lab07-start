# CXX=clang++
CXX=g++

# We have -Wno-unused-parameter so that the compiler
# doesn't complain too much about our stubs.

CXXFLAGS = -g -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field -I/usr/include/jsoncpp
# Change to this before final submission:

#CXXFLAGS = -std=c++11 -Wall -Wextra -Werror



LINK_JSONCPP= -ljsoncpp

LINK_CURLPP= -Wl,-Bsymbolic-functions -Wl,-z,relro -lcurlpp -lstdc++ -lcurl

WORD_COUNTER_TESTS=testWordCounter00  testWordCounter01 testWordCounter02 

TESTS=	${WORD_COUNTER_TESTS} \
	testRedditPost00 testRedditPost01  testRedditPost02 \
	testTfIdfDocument00 testTfIdfDocument01 \
	testTfIdfDocument02 testTfIdfDocument03 \
	testWordHeap00 testWordHeap01 \
	testTfIdfHeap00 testTfIdfHeap01 \
	testCorpus00 testCorpus01 testCorpus02 testCorpus03 \
	integrationTest00 integrationTest01 integrationTest02 integrationTest03


BINARIES= ${TESTS} \
	CurlPPDemo00 \
	DownloadOnePageRedditPosts  DownloadRedditPosts DownloadAllUCsRedditPosts \
	ComputeTwoUCsFromOfflineData ComputeAllUCsFromOfflineData

all: ${BINARIES}

wordCounterTests: ${WORD_COUNTER_TESTS}
	./testWordCounter00
	./testWordCounter01
	./testWordCounter02


test: tests

tests: wordCounterTests
	./testRedditPost01
	./testRedditPost02
	./testTfIdfDocument00
	./testTfIdfDocument01
	./testTfIdfDocument02
	./testTfIdfDocument03
	./testWordHeap00
	./testWordHeap01
	./testTfIdfHeap00
	./testTfIdfHeap01
	./testCorpus00
	./testCorpus01
	./testCorpus02
	./testCorpus03
	./integrationTest00
	./integrationTest01
	./integrationTest02
	./integrationTest03


CurlPPDemo00: CurlPPDemo00.o 
	${CXX} $^ ${LINK_CURLPP}  -o $@

testWordCounter00: testWordCounter00.o WordCounter.o tddFuncs.o
	${CXX} $^ -o $@

testWordCounter01: testWordCounter01.o WordCounter.o tddFuncs.o
	${CXX} $^ -o $@

testWordCounter02: testWordCounter02.o WordCounter.o tddFuncs.o
	${CXX} $^ -o $@


testRedditPost00: testRedditPost00.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -o $@


testRedditPost01: testRedditPost01.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -o $@


testRedditPost02: testRedditPost02.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -o $@

testTfIdfDocument00: testTfIdfDocument00.o tddFuncs.o
	${CXX} $^ -o $@

testTfIdfDocument01: testTfIdfDocument01.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_JSONCPP} -o $@

testTfIdfDocument02: testTfIdfDocument02.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_JSONCPP} -o $@

testTfIdfDocument03: testTfIdfDocument03.o RedditPost.o tddFuncs.o
	${CXX} $^ ${LINK_JSONCPP} -o $@

testWordHeap00: testWordHeap00.o tddFuncs.o
	${CXX} $^ -o $@

testWordHeap01: testWordHeap01.o tddFuncs.o
	${CXX} $^ -o $@

testTfIdfHeap00: testTfIdfHeap00.o tddFuncs.o
	${CXX} $^ -o $@

testTfIdfHeap01: testTfIdfHeap01.o tddFuncs.o
	${CXX} $^ -o $@

testCorpus00: testCorpus00.o tddFuncs.o Corpus.o WordCounter.o
	${CXX} $^ -o $@

testCorpus01: testCorpus01.o tddFuncs.o Corpus.o WordCounter.o
	${CXX} $^ -o $@

testCorpus02: testCorpus02.o tddFuncs.o Corpus.o WordCounter.o
	${CXX} $^ -o $@

testCorpus03: testCorpus03.o tddFuncs.o Corpus.o WordCounter.o
	${CXX} $^ -o $@

integrationTest00: integrationTest00.o  RedditPost.o WordCounter.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

integrationTest01: integrationTest01.o  RedditPost.o WordCounter.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

integrationTest02: integrationTest02.o  RedditPost.o WordCounter.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

integrationTest03: integrationTest03.o  RedditPost.o WordCounter.o tddFuncs.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

DownloadOnePageRedditPosts: DownloadOnePageRedditPosts.o RedditPost.o  RedditPostDownloader.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -o $@

DownloadRedditPosts: DownloadRedditPosts.o RedditPost.o  RedditPostDownloader.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -o $@

DownloadAllUCsRedditPosts: DownloadAllUCsRedditPosts.o RedditPost.o  RedditPostDownloader.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP} -lboost_system -lboost_filesystem -o $@

ComputeAllUCsFromOfflineData: ComputeAllUCsFromOfflineData.o RedditPost.o  RedditPostDownloader.o Corpus.o WordCounter.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

ComputeTwoUCsFromOfflineData: ComputeTwoUCsFromOfflineData.o RedditPost.o  RedditPostDownloader.o Corpus.o WordCounter.o
	${CXX} $^ ${LINK_CURLPP} ${LINK_JSONCPP}  -o $@

clean:
	/bin/rm -f ${BINARIES} *.o
