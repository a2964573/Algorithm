/** 문자 반복 출력하기
 * 문자열 my_string과 정수 n이 매개변수로 주어질 때, 
 * my_string에 들어있는 각 문자를 n만큼 반복한 문자열을 return 하도록 solution 함수를 완성해보세요.
 */
function solution(my_string, n) {
    let answer="";
    my_string.split("").forEach((element)=>{
        for(let i=0; i<n; i++){
            answer+=element;
        }
    })
    return answer;
}