# KnowledgeCrawler

Playing with a C++ project for crawling through markdown notes. I am a big user of [Obsidian](https://obsidian.md/) and, although there is a big Javascript plugin ecosystem, I wanted to explore file processing with C++.

The goal would be to act as a utility for my [Obsidian](https://obsidian.md/) knowledge-base. Currently it can validate intra-note links are valid. However, I have plans to include other features such as:

- Image processing the co-located images
- Sentiment analysis/natural language processing on the note text

All of this could be done ad-hoc as a CLI tool but also in the background by polling the Git repo where the notes are kept and then committing changes back.