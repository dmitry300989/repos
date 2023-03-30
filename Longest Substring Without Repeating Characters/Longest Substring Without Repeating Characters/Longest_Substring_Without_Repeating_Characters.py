class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        return self.FindLongestSubstr(s)
    def FindLongestSubstr(self, string: str):
        l = 0
        dict = {}
        maxL = 0
        startIdx = 0
        for i in range(len(string)):
            l += 1
            if string[i] in dict:
                if dict[string[i]][1] >= startIdx:
                    l = i - dict[string[i]][1]
                    startIdx = dict[string[i]][1] + 1
            dict[string[i]] = [l,i]
            maxL = (l if maxL < l else maxL)
        return maxL

if __name__ == '__main__':
    string = "dvdf"#"ghdjueocdgfshg"
    sol = Solution()
    print(sol.lengthOfLongestSubstring(string))
